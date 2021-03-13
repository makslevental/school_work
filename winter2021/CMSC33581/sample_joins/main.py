import math
import sqlite3
from operator import itemgetter
from typing import List, NamedTuple

import matplotlib.pyplot as plt
import numpy as np
from scipy import stats

con = sqlite3.connect("joins.db")


def get_column_names(table):
    cur = con.cursor()
    names = [r[1] for r in cur.execute(f"""PRAGMA table_info({table});""")]
    cur.close()
    return names


def samp_indices(full_join_name, samp_name):
    cur = con.cursor()
    indices = list(
        cur.execute(
            f"""SELECT {full_join_name}.ROWID FROM {samp_name} NATURAL JOIN {full_join_name};"""
        )
    )

    ((n_rows,),) = cur.execute(f"SELECT COUNT(1) from {full_join_name};")

    cur.close()
    return list(map(itemgetter(0), indices)), n_rows


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
    cur.execute(
        f"""
        CREATE INDEX {tbl_name}_full_idx ON {tbl_name}({",".join(get_column_names(tbl_name))});
        """
    )
    con.commit()
    cur.close()


def naive_sample_f(table_name, f):
    cur = con.cursor()
    ((n_rows,),) = cur.execute(f"SELECT COUNT(1) from {table_name};")
    cur.close()

    return naive_sample_n(table_name, math.ceil(f * n_rows))


def naive_sample_n(table_name, n):
    cur = con.cursor()
    cur.execute(
        f"""CREATE VIEW {table_name}_samp AS SELECT * FROM {table_name} WHERE ROWID IN (SELECT ROWID FROM {table_name} ORDER BY RANDOM() LIMIT {n});"""
    )
    con.commit()
    cur.close()
    return f"{table_name}_samp"


def gen_bens(n=int(1e6), n_digs=2) -> List[int]:
    chi1 = np.random.default_rng().chisquare(df=1, size=n)
    chi2 = np.random.default_rng().chisquare(df=1, size=n)
    bens = [int(f"{b:.5E}".replace(".", "")[:n_digs]) for b in chi1 / chi2]
    return bens


def gen_rel(name, n=int(1e6), attr_names=None):
    if attr_names is None:
        attr_names = ["A", "B"]
    bens = list(zip(*[gen_bens(n) for _ in attr_names], range(1, n + 1)))
    attr_names.append(f"{name}_rowid")
    cur = con.cursor()
    cur.execute(
        f"""CREATE TABLE {name} ({",".join([f"{a} INTEGER" for a in attr_names])});"""
    )
    for attr_name in attr_names:
        cur.execute(
            f"""
            CREATE INDEX {name}_{attr_name}_idx ON {name}({attr_name});
        """
        )
    cur.executemany(
        f"INSERT INTO {name} VALUES ({','.join('?' for _ in attr_names)});", bens
    )
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
    K, n, f = 10, 100, 0.5

    for k in range(2, K):
        prefix = f"tbl_{k}_{n}_{int(f * 100)}"
        rel_names = gen_k_rel(k, n, prefix=prefix)
        # rel_names = ["R0", "R1", "R2", "R3", "R4"]
        n_join(f"{prefix}_full_join", rel_names)
        n_join(f"{prefix}_approx_samp", [naive_sample_f(rel, f) for rel in rel_names])
        samp_indxs, n_rows = samp_indices(
            f"{prefix}_full_join", f"{prefix}_approx_samp"
        )

        plot_n_hists(
            [gen_hist(np.asarray(samp_indxs)), gen_hist(np.asarray(range(n_rows + 1)))],
            labels=["samp", "true"],
        )

        # plt.hist(list(range(n_rows+1)), bins=100, alpha=0.5, label="true")
        # plt.hist(samp_indxs, bins=100, alpha=0.5, label="samp")
        # plt.legend()
        # plt.show()
    # true_samp = naive_sample_n(j, len(approx_samp))
    # print(f"lens {len(j)=} {len(approx_samp)=} {len(true_samp)=}")

    # plot_n_hists(
    #     [
    #         gen_hist(true_samp["A1"].values, n_bins=1000),
    #         gen_hist(approx_samp["A1"].values, n_bins=1000),
    #     ],
    #     labels=["true_samp", "approx_samp"],
    # )
    #
    # kolmogorov_smirnov_test(approx_samp["A1"].values, true_samp["A1"].values)


if __name__ == "__main__":
    # n_join(gen_k_rel(k=3, n=100))
    # print(naive_sample_f("join_table", 0.5))
    # two_join_demo()
    five_join_demo()
    # for _ in range(10):
    #     demo()
