/** @file */
#pragma once
#include "../binary_indexed_tree.hpp"
//TODO: write tests
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
 * @see https://codeforces.com/blog/entry/52854
 * https://github.com/brunomaletta/Biblioteca /blob/master/Codigo/Estruturas/waveletTree.cpp
 */
struct wavelet_tree {
    const int N, MINV, MAXV;
    vector<BIT> tree;
    /**
     * @param arr,minv,maxv must satisfy minv <= arr[i] < maxv
     * @time O((maxv - minv) + n * log(maxv - minv))
     * @space O((maxv - minv) + n * log(maxv - minv)) for `tree`
     */
    wavelet_tree(vector<int> arr, int minv, int maxv) : N(ssize(arr)), MINV(minv), MAXV(maxv), tree(MAXV - MINV, BIT<int>(0)) {
        build(arr, 0, N, MINV, MAXV, 1);
    }
    void build(vector<int>& arr, int le, int ri, int tl, int tr, int v) {
        if (tr - tl <= 1) return;
        int tm = split(tl, tr);
        auto low = [&](int val) -> bool {return val < tm;};
        vector<int> bits(ri - le);
        transform(begin(arr) + le, begin(arr) + ri, begin(bits), low);
        tree[v] = BIT<int>(bits);
        int mi = int(stable_partition(begin(arr) + le, begin(arr) + ri, low) - begin(arr));
        build(arr, le, mi, tl, tm, 2 * v);
        build(arr, mi, ri, tm, tr, 2 * v + 1);
    }
    void set(int idx, bool is_on) {
        assert(0 <= idx && idx < N);
        set_impl(idx, MINV, MAXV, 1);
    }
    void set_impl(int idx, int tl, int tr, int v) const {
        if (tr - tl == 1) return;
        int tm = split(tl, tr), pi = tree[v].sum(idx);
        if () return set_impl(pi, tl, tm, 2 * v);
        set_impl(idx - pi, tm, tr, 2 * v + 1);
    }
    /**
     * @param le,ri,x,y defines rectangle: indexes in [le, ri), values in [x, y)
     * @returns number of indexes i such that le <= i < ri and x <= arr[i] < y
     * @time O(log(maxv - minv) * log(n))
     * @space O(log(maxv - minv)) for recursive stack
     */
    int rect_count(int le, int ri, int x, int y) const {
        assert(0 <= le && le <= ri && ri <= N && x <= y);
        return rect_count_impl(le, ri, x, y, MINV, MAXV, 1);
    }
    int rect_count_impl(int le, int ri, int x, int y, int tl, int tr, int v) const {
        if (y <= tl || tr <= x) return 0;
        if (x <= tl && tr <= y) return ri - le;
        int tm = split(tl, tr), pl = tree[v].sum(le), pr = tree[v].sum(ri);
        return rect_count_impl(pl, pr, x, y, tl, tm, 2 * v) +
               rect_count_impl(le - pl, ri - pr, x, y, tm, tr, 2 * v + 1);
    }
    /**
     * @param le,ri defines range [le, ri)
     * @param k must satisfy 1 <= k <= ri - le
     * @returns kth smallest number in range.
     *     - kth_smallest(le,ri,1) returns the min
     *     - kth_smallest(le,ri,(ri-le)) returns the max
     * @time O(log(maxv - minv) * log(n))
     * @space O(log(maxv - minv)) for recursive stack
     */
    int kth_smallest(int le, int ri, int k) const {
        assert(0 <= le && ri <= N);
        assert(1 <= k && k <= ri - le);
        return kth_smallest_impl(le, ri, k, MINV, MAXV, 1);
    }
    int kth_smallest_impl(int le, int ri, int k, int tl, int tr, int v) const {
        if (tr - tl == 1) return tl;
        int tm = split(tl, tr), pl = tree[v].sum(le), pr = tree[v].sum(ri);
        if (k <= pr - pl) return kth_smallest_impl(pl, pr, k, tl, tm, 2 * v);
        return kth_smallest_impl(le - pl, ri - pr, k - (pr - pl), tm, tr, 2 * v + 1);
    }
};
