/** @file */
#pragma once
#include "bool_presum.hpp"
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
 * https://github.com/brunomaletta/Biblioteca /blob/master/Codigo/Estruturas/mergeSortTree.cpp
 */
struct merge_sort_tree {
    const int N;
    vector<int> sorted;
    vector<bool_presum> bool_presums;
    /**
     * @param arr array
     * @time O(n log n)
     * @space O(n + (n log n) / 64) for `bool_presums` vector
     */
    merge_sort_tree(const vector<int>& arr) : N(ssize(arr)), sorted(N), bool_presums(N, vector<bool>()) {
        vector<pair<int, bool>> cpy(N);
        transform(begin(arr), end(arr), begin(cpy), [](int val) {return pair(val, 0);});
        build(cpy, 0, N, 1);
        transform(begin(cpy), end(cpy), begin(sorted), [](auto val) {return val.first;});
    }
    void build(vector<pair<int, bool>>& cpy, int tl, int tr, int v) {
        if (tr - tl <= 1) return;
        int tm = split(tl, tr);
        build(cpy, tl, tm, 2 * v);
        build(cpy, tm, tr, 2 * v + 1);
        for (int i = tl; i < tr; i++) cpy[i].second = i < tm;
        inplace_merge(begin(cpy) + tl, begin(cpy) + tm, begin(cpy) + tr);
        vector<bool> bools(tr - tl);
        transform(begin(cpy) + tl, begin(cpy) + tr, begin(bools), [](auto val) {return val.second;});
        bool_presums[v] = bool_presum(bools);
    }
    /**
     * @param le,ri,x,y defines rectangle: indexes in [le, ri), values in [x, y)
     * @returns number of indexes i such that le <= i < ri and x <= arr[i] < y
     * @time O(log(n))
     * @space O(log(n)) for recursive stack
     */
    int query(int le, int ri, int x, int y) const {
        assert(0 <= le && le <= ri && ri <= N && x <= y);
        int xi = int(lower_bound(begin(sorted), end(sorted), x) - begin(sorted));
        int yi = int(lower_bound(begin(sorted), end(sorted), y) - begin(sorted));
        return query_impl(le, ri, xi, yi, 0, N, 1);
    }
    int query_impl(int le, int ri, int xi, int yi, int tl, int tr, int v) const {
        if (ri <= tl || tr <= le) return 0;
        if (le <= tl && tr <= ri) return yi - xi;
        int tm = split(tl, tr), pl = bool_presums[v].popcount(xi), pr = bool_presums[v].popcount(yi);
        return query_impl(le, ri, pl, pr, tl, tm, 2 * v) +
               query_impl(le, ri, xi - pl, yi - pr, tm, tr, 2 * v + 1);
    }
    /**
     * @param x,y defines range of values [x, y)
     * @param k must satisfy 1 <= k <= number of indexes i such that x <= arr[i] < y
     * @returns an index i such that arr[i] is the kth smallest value in [x, y)
     *     - kth_smallest(le,ri,1) returns the min
     *     - kth_smallest(le,ri,(ri-le)) returns the max
     * @time O(log(n))
     * @space O(log(n)) for recursive stack
     */
    int kth_smallest(int x, int y, int k) const {
        assert(0 <= le && ri <= N);
        assert(1 <= k && k <= query(0, N, x, y));
        int xi = int(lower_bound(begin(sorted), end(sorted), x) - begin(sorted));
        int yi = int(lower_bound(begin(sorted), end(sorted), y) - begin(sorted));
        return kth_smallest_impl(xi, yi, k, 0, N, 1);
    }
    int kth_smallest_impl(int xi, int yi, int k, int tl, int tr, int v) const {
        if (tr - tl == 1) return tl;
        int tm = split(tl, tr), pl = bool_presums[v].popcount(le), pr = bool_presums[v].popcount(ri);
        if (k <= pr - pl) return kth_smallest_impl(pl, pr, k, tl, tm, 2 * v);
        return kth_smallest_impl(le - pl, ri - pr, k - (pr - pl), tm, tr, 2 * v + 1);
    }
};
