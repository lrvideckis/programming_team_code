/** @file */
#pragma once
#include "persistent_segment_tree.hpp"
/**
 * @see https://cp-algorithms.com/data_structures/segment_tree.html #preserving-the-history-of-its-values-persistent-segment-tree
 */
struct kth_smallest {
    PST pst;
    /**
     * @param arr,minv,maxv must satisfy: minv <= arr[i] < maxv
     * @time O(n log(maxv - minv))
     * @space O(n log(maxv - minv)) nodes are pushed back onto PST::tree
     */
    kth_smallest(const vector<int>& arr, int minv, int maxv) : pst(minv, maxv) {
        for (int i = 0; i < ssize(arr); i++)
            pst.update(arr[i], 1, i);
    }
    /**
     * @param le,ri defines range [le, ri)
     * @param k must satisfy 1 <= k <= ri - le
     * @returns kth smallest number in range.
     *     - query(le,ri,1) returns the min
     *     - query(le,ri,(ri-le)) returns the max
     * @time O(log(maxv - minv))
     * @space O(log(maxv - minv)) for recursion stack; no new nodes are allocated
     */
    int query(int le, int ri, int k) const {
        assert(0 <= le && ri < ssize(pst.roots));
        assert(1 <= k && k <= ri - le);
        return query_impl(k, pst.ROOT_L, pst.ROOT_R, pst.roots[le], pst.roots[ri]);
    }
    int query_impl(int k, int tl, int tr, int vl, int vr) const {
        if (tr - tl == 1) return tl;
        int tm = tl + (tr - tl) / 2;
        int left_count = int(pst.tree[pst.tree[vr].lch].sum - pst.tree[pst.tree[vl].lch].sum);
        if (left_count >= k) return query_impl(k, tl, tm, pst.tree[vl].lch, pst.tree[vr].lch);
        return query_impl(k - left_count, tm, tr, pst.tree[vl].rch, pst.tree[vr].rch);
    }
};
