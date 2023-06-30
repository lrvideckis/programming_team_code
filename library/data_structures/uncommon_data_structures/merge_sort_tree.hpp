/** @file */
#pragma once
#include "bit_presum.hpp"
/**
 * @see https://codeforces.com/blog/entry/112755
 * @param tl,tr defines range [tl, tr)
 * @returns split point of range which makes the merge sort tree a complete
 * binary tree
 */
inline int split(int tl, int tr) {
    int pw2 = 1 << __lg(tr - tl);
    return min(tl + pw2, tr - pw2 / 2);
}
/**
 * For point updates: either switch to merge sort tree with policy based BST, use sqrt
 * decomposition, or wavelet tree
 */
struct merge_sort_tree {
    const int N;
    vector<int> arr;
    vector<bit_presum> bit_presums;
    /**
     * @param a_arr array
     * @time O(n log n)
     * @space O(n + (n log n) / 64) for `bit_presums` vector
     */
    merge_sort_tree(const vector<int>& a_arr) : N(ssize(a_arr)), arr(N), bit_presums(N, vector<bool>()) {
        vector<pair<int, bool>> cpy(N);
        transform(begin(a_arr), end(a_arr), begin(cpy), [](int val) {return pair(val, 0);});
        build(cpy, 0, N, 1);
        transform(begin(cpy), end(cpy), begin(arr), [](auto val) {return val.first;});
    }
    void build(vector<pair<int, bool>>& cpy, int tl, int tr, int v) {
        if (tr - tl <= 1) return;
        int tm = split(tl, tr);
        build(cpy, tl, tm, 2 * v);
        build(cpy, tm, tr, 2 * v + 1);
        for (int i = tl; i < tr; i++) cpy[i].second = i < tm;
        inplace_merge(begin(cpy) + tl, begin(cpy) + tm, begin(cpy) + tr);
        vector<bool> bits(tr - tl);
        transform(begin(cpy) + tl, begin(cpy) + tr, begin(bits), [](auto val) {return val.second;});
        bit_presums[v] = bit_presum(bits);
    }
    /**
     * @param le,ri,x,y defines rectangle: indexes in [le, ri), values in [x, y)
     * @returns sum of values arr[i] such that le <= i < ri and x <= arr[i] < y
     * @time O(log(n))
     * @space O(log(n)) for recursive stack
     */
    int query(int le, int ri, int x, int y) const {
        assert(0 <= le && le <= ri && ri <= N && x <= y);
        auto idx = [&](int val) -> int {
            return arr.empty() ? 0 : int(lower_bound(begin(arr), end(arr), val) - begin(arr));
        };
        return query_impl(le, ri, idx(x), idx(y), 0, N, 1);
    }
    int query_impl(int le, int ri, int xi, int yi, int tl, int tr, int v) const {
        if (ri <= tl || tr <= le) return 0;
        if (le <= tl && tr <= ri) return yi - xi;
        int tm = split(tl, tr), pl = bit_presums[v].popcount(xi), pr = bit_presums[v].popcount(yi);
        return query_impl(le, ri, pl, pr, tl, tm, 2 * v) +
               query_impl(le, ri, xi - pl, yi - pr, tm, tr, 2 * v + 1);
    }
};
