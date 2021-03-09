import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from scipy import stats

INDEX_COL = "vals"


def kolmogorov_smirnov_test(rvs1: np.ndarray, rvs2: np.ndarray):
    # https://en.wikipedia.org/wiki/Kolmogorov%E2%80%93Smirnov_test#Two-sample_Kolmogorov%E2%80%93Smirnov_test
    #
    # null hypothesis => same distribution
    # low prval or high stat => reject null => diff distributions

    assert len(rvs1) == len(rvs2)
    stat, pval = stats.ks_2samp(rvs1, rvs2)
    print(f"n={len(rvs1)} samples; stat={stat:.4f}; p={pval:.4f} ")
    return stat, pval


def join(
    df1: pd.DataFrame, df2: pd.DataFrame, how="inner", check=False
) -> pd.DataFrame:
    j = df1.merge(df2, on=INDEX_COL, how=how, sort=True, indicator=check)
    return j


def naive_sample_fraction(df: pd.DataFrame, f: float, replace=True) -> pd.DataFrame:
    return df.sample(frac=f, replace=replace, random_state=1)


def naive_sample_n(df: pd.DataFrame, n: int, replace=True) -> pd.DataFrame:
    return df.sample(n=n, replace=replace, random_state=1)


def gen_bens(n=int(10e6)) -> pd.DataFrame:
    chi1 = np.random.default_rng().chisquare(df=1, size=n)
    chi2 = np.random.default_rng().chisquare(df=1, size=n)
    bens = [int(f"{b:.1E}".replace(".", "")[:2]) for b in chi1 / chi2]
    return pd.DataFrame({INDEX_COL: bens})


def naive_join_sample(re1: pd.DataFrame, re2: pd.DataFrame, f: float) -> pd.DataFrame:
    samp1 = naive_sample_fraction(re1, f)
    samp2 = naive_sample_fraction(re2, f)
    return join(samp1, samp2)


def hist(df: pd.DataFrame, n_bins=100):
    density, bin_edges = np.histogram(df[INDEX_COL], n_bins, density=True)
    # bin_width = (df[INDEX_COL].max() - df[INDEX_COL].min()) / n_bins
    # cdf = np.cumsum(density * bin_width)
    # assert np.isclose(cdf[-1], 1)
    return density, bin_edges


def plot_hist(density, bin_edges):
    bin_center = 0.5 * (bin_edges[1:] + bin_edges[:-1])
    plt.fill_between(bin_center, density, step="pre", alpha=0.4)
    plt.plot(bin_center, density, drawstyle="steps")
    plt.grid(True)
    plt.show()


def demo():
    f = 0.5
    rel1 = gen_bens(n=100)
    rel2 = gen_bens(n=100)
    rel1_rel2 = join(rel1, rel2)
    approx_samp = naive_join_sample(rel1, rel2, f)
    true_samp = naive_sample_n(rel1_rel2, len(approx_samp))

    # density, bin_edges = hist(true_samp)
    # plot_hist(density, bin_edges)
    # density, bin_edges = hist(approx_samp)
    # plot_hist(density, bin_edges)

    kolmogorov_smirnov_test(
        approx_samp[INDEX_COL].values, true_samp[INDEX_COL].values
    )


if __name__ == "__main__":
    for _ in range(10):
        demo()
