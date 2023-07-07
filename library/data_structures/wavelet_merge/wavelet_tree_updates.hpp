/** @file */
#pragma once
#include "bool_presum.hpp"
#include "bool_bit.hpp"
/**
 * @see https://codeforces.com/blog/entry/112755
 * @param tl,tr defines range [tl, tr)
 * @returns split point of range which makes the wavelet tree a complete
 * binary tree
 */
inline int split(int tl, int tr) {
    int pw2 = 1 << __lg(tr - tl);
    return min(tl + pw2, tr - pw2 / 2);
}
/**
 * @see https://ioinformatics.org/journal/v10_2016_19_37.pdf
 * https://github.com/brunomaletta/Biblioteca /blob/master/Codigo/Estruturas/waveletTree.cpp
 */
struct wavelet_tree_updates {
    const int N, MINV, MAXV;
    vector<bool_presum> bool_presums;
    vector<bool_bit> bool_bits;
    /**
     * @code{.cpp}
     *     vector<int> arr;
     *     ...
     *     vector<int> sorted(arr);
     *     sort(begin(sorted), end(sorted));
     *     sorted.erase(unique(begin(sorted), end(sorted)), end(sorted));
     *     for (int& val : arr) val = int(lower_bound(begin(sorted), end(sorted), val) - begin(sorted));
     *     wavelet_tree_updates(arr, 0, ssize(sorted));
     * @endcode
     * @param arr,minv,maxv must satisfy minv <= arr[i] < maxv
     * @param active_state active_state[i] == 1 iff index i is initially active
     * @time O((maxv - minv) + n * log(maxv - minv))
     * @space O((maxv - minv) + n * log(maxv - minv) / 64) for `bool_presums` and for `bool_bits`
     */
    wavelet_tree_updates(const vector<int>& arr, int minv, int maxv, const vector<bool>& active_state) : N(ssize(arr)), MINV(minv), MAXV(maxv), bool_presums(MAXV - MINV, vector<bool>()), bool_bits(2 * (MAXV - MINV), 0) {
        assert(minv < maxv);
        build(arr, 0, N, MINV, MAXV, 1);
    }
    void build(vector<int>& arr, int le, int ri, int tl, int tr, int v) {
        bool_bits[v] = bool_bit(ri - le);
        if (tr - tl <= 1) return;
        int tm = split(tl, tr);
        auto low = [&](int val) -> bool {return val < tm;};
        vector<bool> bools(ri - le);
        transform(begin(arr) + le, begin(arr) + ri, begin(bools), low);
        bool_presums[v] = bool_presum(bools);
        int mi = int(stable_partition(begin(arr) + le, begin(arr) + ri, low) - begin(arr));
        build(arr, le, mi, tl, tm, 2 * v);
        build(arr, mi, ri, tm, tr, 2 * v + 1);
    }
    /**
     * @param i index
     * @param is_active we want to set active_state[i] = is_active
     * @time O(log(maxv - minv) * log(n / 64))
     * @space O(log(maxv - minv)) for recursive stack
     */
    void set_active(int i, bool is_active) {
        assert(0 <= i && i < N);
        if (bool_bits[1].on(i) == is_active) return;
        set_active_impl(i, is_active, MINV, MAXV, 1);
    }
    void set_active_impl(int i, bool is_active, int tl, int tr, int v) {
        bool_bits[v].set(i, is_active);
        if (tr - tl == 1) return;
        int tm = split(tl, tr), pi = bool_presums[v].popcount(i);
        if (bool_presums[v].on(i)) return set_active_impl(pi, is_active, tl, tm, 2 * v);
        set_active_impl(i - pi, is_active, tm, tr, 2 * v + 1);
    }
    /**
     * @param le,ri,x,y defines rectangle: indexes in [le, ri), values in [x, y)
     * @returns number of active indexes i such that le <= i < ri and x <= arr[i] < y
     * @time O(log(maxv - minv) * log(n / 64))
     * @space O(log(maxv - minv)) for recursive stack
     */
    int rect_count(int le, int ri, int x, int y) const {
        assert(0 <= le && le <= ri && ri <= N && x <= y);
        return rect_count_impl(le, ri, x, y, MINV, MAXV, 1);
    }
    int rect_count_impl(int le, int ri, int x, int y, int tl, int tr, int v) const {
        if (y <= tl || tr <= x) return 0;
        if (x <= tl && tr <= y) return bool_bits[v].popcount(le, ri);
        int tm = split(tl, tr), pl = bool_presums[v].popcount(le), pr = bool_presums[v].popcount(ri);
        return rect_count_impl(pl, pr, x, y, tl, tm, 2 * v) +
               rect_count_impl(le - pl, ri - pr, x, y, tm, tr, 2 * v + 1);
    }
    /**
     * @param le,ri defines range [le, ri)
     * @param k must satisfy 1 <= k <= # active indexes in [le, ri)
     * @returns kth smallest active number in range.
     *     - kth_smallest(le,ri,1) returns the smallest active number
     *     - kth_smallest(le,ri,rect_count(le,ri,-INF,INF)) returns the largest active number
     * @time O(log(maxv - minv) * log(n / 64))
     * @space O(log(maxv - minv)) for recursive stack
     */
    int kth_smallest(int le, int ri, int k) const {
        assert(0 <= le && ri <= N);
        assert(1 <= k && k <= bool_bits[1].popcount(le, ri));
        return kth_smallest_impl(le, ri, k, MINV, MAXV, 1);
    }
    int kth_smallest_impl(int le, int ri, int k, int tl, int tr, int v) const {
        if (tr - tl == 1) return tl;
        int tm = split(tl, tr), pl = bool_presums[v].popcount(le), pr = bool_presums[v].popcount(ri);
        int cnt_left = bool_bits[2 * v].popcount(pl, pr);
        if (k <= cnt_left) return kth_smallest_impl(pl, pr, k, tl, tm, 2 * v);
        return kth_smallest_impl(le - pl, ri - pr, k - cnt_left, tm, tr, 2 * v + 1);
    }
};
