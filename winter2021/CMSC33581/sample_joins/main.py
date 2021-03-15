import math
import pickle
from typing import List, NamedTuple

import matplotlib.pyplot as plt
import numpy as np
import psycopg2
from scipy import stats

con = psycopg2.connect(
    "host=localhost dbname=postgres user=postgres password=mysecretpassword"
)


def get_freqs(tbl, col):
    q = f"""SELECT {col},
        COUNT({col})
        FROM {tbl}
        GROUP BY {col}
    """
    cur = con.cursor()
    cur.execute(q)
    counts = {v: cnt for v, cnt in cur.fetchall()}
    cur.close()
    return counts


def get_column_names(table):
    cur = con.cursor()
    cur.execute(f"SELECT * FROM {table} LIMIT 0")
    names = [desc[0] for desc in cur.description]
    return names


def get_common_col(tbl1, tbl2):
    col_names_1 = get_column_names(tbl1)
    col_names_2 = get_column_names(tbl2)
    common_col = set(col_names_1) & set(col_names_2)
    assert len(common_col) == 1
    common_col = common_col.pop()
    return common_col


def get_all_indices_map(table):
    cur = con.cursor()
    cur.execute(f"""SELECT {table}.ctid FROM {table};""")
    indices = {ctid: i for i, (ctid,) in enumerate(cur.fetchall())}
    return indices


def samp_indices(full_join_name, samp_name):
    cur = con.cursor()
    full_indices = get_all_indices_map(full_join_name)
    cur.execute(
        f"""SELECT {full_join_name}.ctid FROM {samp_name} NATURAL JOIN {full_join_name};"""
    )
    samp_indices = [full_indices[ctid] for i, (ctid,) in enumerate(cur.fetchall())]
    cur.close()
    return samp_indices, np.array(list(full_indices.values()))


def sample_one(tbl):
    cur = con.cursor()
    q = f"""SELECT * FROM {tbl} WHERE ctid IN (SELECT ctid FROM {tbl} ORDER BY RANDOM() LIMIT 1)"""
    cur.execute(q)
    res = cur.fetchone()
    cur.close()
    if res is not None:
        return res
    else:
        raise Exception("no sample")


def sample_one_matching(tbl, col_name, val):
    cur = con.cursor()
    q = f"""SELECT * FROM {tbl} WHERE ctid IN (SELECT ctid FROM {tbl} WHERE {tbl}.{col_name}={val} ORDER BY RANDOM() LIMIT 1)"""
    cur.execute(q)
    res = cur.fetchone()
    cur.close()
    return res


def sample_indices(full_join_name, samples):
    cur = con.cursor()
    full_indices = get_all_indices_map(full_join_name)
    column_names = get_column_names(full_join_name)
    assert set(column_names) == samples[0].keys()

    samp_indices = []
    for sample in samples:
        q = f"""SELECT ctid FROM {full_join_name} WHERE {" AND ".join([f"{k}={v}" for k, v in sample.items()])}"""
        cur.execute(q)
        res = cur.fetchone()
        if res is not None:
            (ctid,) = res
            samp_indices.append(full_indices[ctid])
    cur.close()
    return np.array(samp_indices), np.array(list(full_indices.values()))


def kolmogorov_smirnov_test(rvs1: np.ndarray, rvs2: np.ndarray):
    # https://en.wikipedia.org/wiki/Kolmogorov%E2%80%93Smirnov_test#Two-sample_Kolmogorov%E2%80%93Smirnov_test
    #
    # null hypothesis => same distribution
    # low prval or high stat => reject null => diff distributions

    assert len(rvs1) == len(rvs2)
    stat, pval = stats.ks_2samp(rvs1, rvs2)
    print(f"n={len(rvs1)} samples; stat={stat:.4f}; p={pval:.4f} ")
    return stat, pval


def two_join(tbl_name, table_name_1, table_name_2, view_or_tbl="TABLE"):
    cur = con.cursor()
    # sample rels are views
    if view_or_tbl == "VIEW":
        cur.execute(f"""DROP MATERIALIZED VIEW IF EXISTS {tbl_name} CASCADE;""")
        cur.execute(
            f"""CREATE MATERIALIZED VIEW {tbl_name} AS SELECT * FROM {table_name_1} NATURAL JOIN {table_name_2};"""
        )
        con.commit()
    else:
        cur.execute(
            f"""CREATE TABLE IF NOT EXISTS {tbl_name} AS SELECT * FROM {table_name_1} NATURAL JOIN {table_name_2};"""
        )
        con.commit()
    cur.close()
    return tbl_name


def n_join(tbl_name, rel_names, view_or_tbl="TABLE"):
    cur = con.cursor()
    # sample rels are views
    if view_or_tbl == "VIEW":
        cur.execute(f"""DROP MATERIALIZED VIEW IF EXISTS {tbl_name} CASCADE;""")
        cur.execute(
            f"""CREATE MATERIALIZED VIEW {tbl_name} AS SELECT * FROM {" NATURAL JOIN ".join(rel_names)};"""
        )
        con.commit()
    else:
        cur.execute(
            f"""CREATE TABLE IF NOT EXISTS {tbl_name} AS SELECT * FROM {" NATURAL JOIN ".join(rel_names)};"""
        )
        con.commit()

    q = f"""
        CREATE INDEX IF NOT EXISTS {tbl_name}_complete_idx ON {tbl_name}({",".join(get_column_names(tbl_name))});
    """
    cur.execute(q)
    con.commit()
    cur.close()


def get_n_rows(table_name):
    cur = con.cursor()
    cur.execute(f"SELECT COUNT(1) from {table_name};")
    (n_rows,) = cur.fetchone()
    cur.close()
    return n_rows


def naive_sample_f(table_name, f):
    n_rows = get_n_rows(table_name)
    return naive_sample_n(table_name, math.ceil(f * n_rows))


def naive_sample_n(table_name, n):
    cur = con.cursor()
    # sample rels are views
    cur.execute(f"""DROP MATERIALIZED VIEW IF EXISTS {table_name}_samp CASCADE;""")
    con.commit()

    cur.execute(
        f"""CREATE MATERIALIZED VIEW {table_name}_samp AS SELECT * FROM {table_name} WHERE ctid IN (SELECT ctid FROM {table_name} ORDER BY RANDOM() LIMIT {n});"""
    )
    con.commit()
    cur.close()
    return f"{table_name}_samp"


def wander_sample_n(rels, n):
    cur = con.cursor()

    samples = []
    for i in range(n):
        res = dict(zip(get_column_names(rels[0]), sample_one(rels[0])))

        for rel in rels[1:]:
            col_names = get_column_names(rel)
            common_col = res.keys() & set(col_names)
            assert len(common_col) == 1
            common_col = common_col.pop()

            q = f"""SELECT * FROM {rel} WHERE ctid IN (SELECT ctid FROM {rel} WHERE {rel}.{common_col}={res[common_col]} ORDER BY RANDOM() LIMIT 1)"""
            cur.execute(q)
            row = cur.fetchone()
            if row is not None:
                res.update(dict(zip(col_names, row)))
            else:
                break
        else:
            samples.append(res)
            continue
        # break
    cur.close()
    return samples


def olken_sample_two_n(table_name_1, table_name_2, n):
    col_names_1 = get_column_names(table_name_1)
    col_names_to_idx_1 = {name: idx for idx, name in enumerate(col_names_1)}
    col_names_2 = get_column_names(table_name_2)
    col_names_to_idx_2 = {name: idx for idx, name in enumerate(col_names_2)}
    common_col = get_common_col(table_name_1, table_name_2)
    m2 = get_freqs(table_name_2, common_col)
    M = max(m2.values())

    S = [col_names_1 + col_names_2]

    while len(S) < n:
        t1 = sample_one(table_name_1)
        t2 = sample_one_matching(
            table_name_2, common_col, t1[col_names_to_idx_1[common_col]]
        )
        while t2 is None:
            t1 = sample_one(table_name_1)
            t2 = sample_one_matching(
                table_name_2, common_col, t1[col_names_to_idx_1[common_col]]
            )
        if m2[t2[col_names_to_idx_2[common_col]]] < np.random.randint(0, M):
            continue

        S.append(dict(zip(col_names_1, t1)))
        S[-1].update(dict(zip(col_names_2, t2)))

    return S

def weighted_wr_sample(table, n, weights, weight_col_name):
    col_names = get_column_names(table)
    col_names_to_idx = {name: idx for idx, name in enumerate(col_names)}

    cur = con.cursor()
    W = 0
    A = n*[None]

    cur.execute(f"SELECT * FROM {table}")

    row = cur.fetchone()
    while row:
        w = weights[row[col_names_to_idx[weight_col_name]]]
        W += w
        for j in range(len(A)):
            if np.random.random() <= w/W:
                A[j] = row

        row = cur.fetchone()

    cur.close()
    return A


def stream_sample_two(table_name_1, table_name_2, n):
    col_names_1 = get_column_names(table_name_1)
    col_names_to_idx_1 = {name: idx for idx, name in enumerate(col_names_1)}
    col_names_2 = get_column_names(table_name_2)
    col_names_to_idx_2 = {name: idx for idx, name in enumerate(col_names_2)}
    common_col = get_common_col(table_name_1, table_name_2)
    m2 = get_freqs(table_name_2, common_col)

    table_1_samples = weighted_wr_sample(table_name_1, n, m2, common_col)
    samples = [col_names_1 + col_names_2]
    for t1 in table_1_samples:
        v = t1[col_names_to_idx_1[common_col]]
        t2 = sample_one_matching(table_name_2, common_col, v)

        samples.append(dict(zip(col_names_1, t1)))
        samples[-1].update(dict(zip(col_names_2, t2)))

    return samples

def gen_bens(n=int(1e6), n_digs=2) -> List[int]:
    chi1 = np.random.default_rng().chisquare(df=1, size=n)
    chi2 = np.random.default_rng().chisquare(df=1, size=n)
    bens = [int(f"{b:.5E}".replace(".", "")[:n_digs]) for b in chi1 / chi2]
    return bens


def gen_rel(name, n=int(1e6), attr_names=None):
    if attr_names is None:
        attr_names = ["A", "B"]
    bens = list(zip(*[gen_bens(n) for _ in attr_names], range(1, n + 1)))
    attr_names.append(f"{name}_ctid")
    cur = con.cursor()
    q = f"""CREATE TABLE IF NOT EXISTS {name} ({",".join([f"{a} int" for a in attr_names])});"""
    cur.execute(q)
    for attr_name in attr_names:
        cur.execute(
            f"""
            CREATE INDEX IF NOT EXISTS {name}_{attr_name}_idx ON {name}({attr_name});
        """
        )
    for tup in bens:
        cur.execute(f"INSERT INTO {name}({','.join(attr_names)}) VALUES {tup};")
    con.commit()
    cur.close()


def gen_k_rel(k=2, n=int(1e6), prefix="") -> List[str]:
    names = []
    for i in range(k):
        name = f"{prefix}_R{i}"
        gen_rel(name, n, attr_names=[f"A{i}", f"A{i + 1}"])
        names.append(name)
    return names


class Hist(NamedTuple):
    density: np.ndarray
    bin_edges: np.ndarray


def gen_hist(vals: np.ndarray, n_bins=100):
    density, bin_edges = np.histogram(vals, n_bins, density=True)
    # bin_width = (df[INDEX_COL].max() - df[INDEX_COL].min()) / n_bins
    # cdf = np.cumsum(density * bin_width)
    # assert np.isclose(cdf[-1], 1)
    return Hist(density, bin_edges)


def plot_hist_ax(ax: plt.Axes, density, bin_edges, label):
    bin_center = 0.5 * (bin_edges[1:] + bin_edges[:-1])
    ax.fill_between(bin_center, density, step="pre", alpha=0.2)
    ax.plot(bin_center, density, drawstyle="steps", label=label, alpha=0.5)


def plot_n_hists(hists: List[Hist], title="", labels=None):
    if labels is None:
        labels = [f"hist{i}" for i in range(len(hists))]
    fig, ax = plt.subplots()

    for i, hist in enumerate(hists):
        plot_hist_ax(ax, hist.density, hist.bin_edges, labels[i])

    ax.set_title(title)
    ax.legend()
    ax.grid(True)
    fig.show()


def loop_all_exps(K, N, loop_body):
    # K, N = 5, 1000
    for k in range(2, K):
        for f in np.linspace(0.1, 0.9, 9):
            prefix = f"tbl_{k}_{N}_{int(f * 100)}"
            loop_body(k, N, f, prefix)

    # K, N = 3, 10000
    # for k in range(2, K):
    #     for f in np.linspace(0.1, 0.9, 9):
    #         prefix = f"tbl_{k}_{N}_{int(f * 100)}"
    #         loop_body(k, N, f, prefix)


def gen_exps():
    def loop_body(k, N, f, prefix):
        rel_names = gen_k_rel(k, N, prefix=prefix)
        n_join(f"{prefix}_full_join", rel_names)

    loop_all_exps(5, 1000, loop_body)
    loop_all_exps(3, 10000, loop_body)


def wander_join_exps():
    def loop_body(k, N, f, prefix):
        print(f"{k},{N},{f},{prefix}")
        rels = [f"r{i}" for i in range(k)]
        n_rows = get_n_rows(f"{prefix}_full_join")
        samples = wander_sample_n(
            [f"{prefix}_{r}" for r in rels], math.ceil(f * n_rows)
        )
        samp_indxs, full_indxs = sample_indices(f"{prefix}_full_join", samples[1:])
        pickle.dump(
            {"samp_indxs": samp_indxs, "full_indxs": full_indxs},
            open(
                f"/home/maksim/dev_projects/school_work/winter2021/CMSC33581/sample_joins/{prefix}_wanderjoin.p",
                "wb",
            ),
        )

    loop_all_exps(5, 1000, loop_body)
    loop_all_exps(3, 10000, loop_body)


def olken_join_exps():
    def loop_body(k, N, f, prefix):
        print(f"{k},{N},{f},{prefix}")
        rels = [f"r{i}" for i in range(k)]
        n_rows = get_n_rows(f"{prefix}_full_join")
        samples = olken_sample_two_n(
            *[f"{prefix}_{r}" for r in rels], math.ceil(f * n_rows)
        )
        samp_indxs, full_indxs = sample_indices(f"{prefix}_full_join", samples[1:])
        pickle.dump(
            {"samp_indxs": samp_indxs, "full_indxs": full_indxs},
            open(
                f"/home/maksim/dev_projects/school_work/winter2021/CMSC33581/sample_joins/{prefix}_olkenjoin.p",
                "wb",
            ),
        )

    loop_all_exps(3, 10000, loop_body)

def stream_sample_exps(N):
    def loop_body(k, N, f, prefix):
        print(f"{k},{N},{f},{prefix}")
        rels = [f"r{i}" for i in range(k)]
        n_rows = get_n_rows(f"{prefix}_full_join")
        samples = stream_sample_two(
            *[f"{prefix}_{r}" for r in rels], math.ceil(f * n_rows)
        )
        samp_indxs, full_indxs = sample_indices(f"{prefix}_full_join", samples[1:])
        pickle.dump(
            {"samp_indxs": samp_indxs, "full_indxs": full_indxs},
            open(
                f"/home/maksim/dev_projects/school_work/winter2021/CMSC33581/sample_joins/{prefix}_streamjoin.p",
                "wb",
            ),
        )

    loop_all_exps(3, N, loop_body)

if __name__ == "__main__":
    # gen_exps()
    # print(get_freqs("tbl_2_1000_10_r0", "A0"))
    # olken_join_exps()
    # freqs = get_freqs("tbl_2_1000_10_r1", "A1")
    # print(weighted_wr_sample("tbl_2_1000_10_r0", 100, freqs, "a1"))
    # print(stream_sample_two("tbl_2_1000_10_r0", "tbl_2_1000_10_r1", 10))
    stream_sample_exps(10000)