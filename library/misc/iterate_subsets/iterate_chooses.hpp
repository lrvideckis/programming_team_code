/** @file */
#pragma once
/**
 * @see https://github.com/kth-competitive-programming/
 *     kactl/blob/main/content/various/chapter.tex
 * @param mask a number with k bits set
 * @returns the smallest number x such that:
 * - x has k bits set
 * - x > mask
 * @time O(1)
 */
int next_subset(int mask) {
    int c = mask & -mask, r = mask + c;
    return r | (((r ^ mask) >> 2) / c);
}
/**
 * @author camc
 * @param n,k defines which bitmasks
 * @param func called on all bitmasks of size n with k bits set
 * @time O(n choose k)
 * @memory O(1)
 */
template <typename F> void iterate_chooses(int n, int k, const F& func) {
    for (int mask = (1 << k) - 1; mask < (1 << n); mask = next_subset(mask))
        func(mask);
}
