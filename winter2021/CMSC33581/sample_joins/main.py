import math
from typing import List, NamedTuple

import matplotlib.pyplot as plt
import numpy as np
import psycopg2
from scipy import stats

con = psycopg2.connect(
    "host=localhost dbname=postgres user=postgres password=mysecretpassword"
)


def get_column_names(table):
    cur = con.cursor()
    cur.execute(f"SELECT * FROM {table} LIMIT 0")
    names = [desc[0] for desc in cur.description]
    return names


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


def sample_indices(full_join_name, samples):
    cur = con.cursor()
    full_indices = get_all_indices_map(full_join_name)
    column_names = get_column_names(full_join_name)
    assert set(column_names) == samples[0].keys()

    samp_indices = []
    for sample in samples:
        q = f"""SELECT ctid FROM {full_join_name} WHERE {" AND ".join([f"{k}={v}" for k, v in sample.items()])}"""
        cur.execute(q)
        ((ctid,),) = cur.fetchall()
        samp_indices.append(full_indices[ctid])
    cur.close()
    return samp_indices, np.array(list(full_indices.values()))


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
    cur.execute(
        f"""CREATE {view_or_tbl} {tbl_name} AS SELECT * FROM {table_name_1} NATURAL JOIN {table_name_2};"""
    )
    con.commit()
    cur.close()
    return tbl_name


def n_join(tbl_name, rel_names, view_or_tbl="TABLE"):
    cur = con.cursor()
    cur.execute(
        f"""CREATE {view_or_tbl} {tbl_name} AS SELECT * FROM {" NATURAL JOIN ".join(rel_names)};"""
    )
    con.commit()
    q = f"""
    CREATE INDEX {tbl_name}_complete_idx ON {tbl_name}({",".join(get_column_names(tbl_name))});
    """
    cur.execute(q)
    con.commit()
    cur.close()


def naive_sample_f(table_name, f):
    cur = con.cursor()
    cur.execute(f"SELECT COUNT(1) from {table_name};")
    ((n_rows,),) = cur.fetchall()
    cur.close()

    return naive_sample_n(table_name, math.ceil(f * n_rows))


def naive_sample_n(table_name, n):
    cur = con.cursor()
    cur.execute(
        f"""CREATE VIEW {table_name}_samp AS SELECT * FROM {table_name} WHERE ctid IN (SELECT ctid FROM {table_name} ORDER BY RANDOM() LIMIT {n});"""
    )
    con.commit()
    cur.close()
    return f"{table_name}_samp"


def wander_sample_n(rels, n):
    cur = con.cursor()

    samples = []
    for i in range(n):
        q = f"""SELECT * FROM {rels[0]} WHERE ctid IN (SELECT ctid FROM {rels[0]} ORDER BY RANDOM() LIMIT 1)"""
        cur.execute(q)
        res = dict(zip(get_column_names(rels[0]), cur.fetchone()))

        for rel in rels[1:]:
            col_names = get_column_names(rel)
            common_col = res.keys() & set(col_names)
            assert len(common_col) == 1
            common_col = common_col.pop()
            q = f"""SELECT * FROM {rel} WHERE ctid IN (SELECT ctid FROM {rel} WHERE {rel}.{common_col}={res[common_col]} ORDER BY RANDOM() LIMIT 1)"""
            cur.execute(q)
            row = cur.fetchone()
            if row:
                res |= dict(zip(col_names, row))
            else:
                break
        else:
            samples.append(res)
            continue
        # break
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
    q = f"""CREATE TABLE {name} ({",".join([f"{a} int" for a in attr_names])});"""
    cur.execute(q)
    for attr_name in attr_names:
        cur.execute(
            f"""
            CREATE INDEX {name}_{attr_name}_idx ON {name}({attr_name});
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


def five_join_demo():
    K, n, f = 5, 1000, 0.5

    for k in range(2, K):
        prefix = f"tbl_{k}_{n}_{int(f * 100)}"
        rel_names = gen_k_rel(k, n, prefix=prefix)
        # rel_names = ["R0", "R1", "R2", "R3", "R4"]
        n_join(f"{prefix}_full_join", rel_names)
        n_join(f"{prefix}_approx_samp", [naive_sample_f(rel, f) for rel in rel_names])
        samp_indxs, full_indxs = samp_indices(
            f"{prefix}_full_join", f"{prefix}_approx_samp"
        )

        plot_n_hists(
            [gen_hist(np.asarray(samp_indxs)), gen_hist(full_indxs)],
            labels=["samp", "true"],
        )

    # kolmogorov_smirnov_test(approx_samp["A1"].values, true_samp["A1"].values)


def wander_join_demo():
    prefix = "tbl_4_1000_50"
    samples = wander_sample_n([f"{prefix}_{t}" for t in ["r0", "r1", "r2", "r3"]], 100)
    samp_indxs, full_indxs = sample_indices(f"{prefix}_full_join", samples[1:])

    plot_n_hists(
        [gen_hist(np.asarray(samp_indxs)), gen_hist(full_indxs)],
        labels=["samp", "true"],
    )


if __name__ == "__main__":
    wander_join_demo()
    # n_join(gen_k_rel(k=3, n=100))
    # print(naive_sample_f("join_table", 0.5))
    # two_join_demo()
    # five_join_demo()

    # wander_sample_n()
    # for _ in range(10):
    #     demo()
