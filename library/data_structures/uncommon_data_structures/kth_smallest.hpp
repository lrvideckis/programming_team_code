/** @file */
#pragma once
#include "persistent_segment_tree.hpp"
/**
 * @see https://cp-algorithms.com/data_structures/segment_tree.html
 *     preserving-the-history-of-its-values-persistent-segment-tree
 */
struct kth_smallest {
    PST pst;
    /**
     * @param arr static array; can't handle updates
     * @time O(n log(mx - mn))
     * @space O(n log(mx - mn)) on heap
     */
    kth_smallest(const vector<int>& arr) : pst(init(arr)) {
        for (int i = 0; i < ssize(arr); i++)
            pst.update(arr[i], 1, i);
    }
    static PST init(const vector<int>& arr) {
        auto [mn, mx] = minmax_element(begin(arr), end(arr));
        return {*mn, *mx + 1};
    }
    /**
     * @param le,ri defines range [le, ri)
     * @param k query parameter
     * @returns (k+1)th smallest number in range. k is 0-based, so
     * query(le,ri,0) returns the min
     * @time O(log(mx - mn))
     * @space O(log(mx - mn)) on stack, O(1) on heap
     */
    int query(int le, int ri, int k) const {
        assert(0 <= k && k < ri - le);
        assert(0 <= le && ri < ssize(pst.roots));
        return query_impl(k, pst.ROOT_L, pst.ROOT_R, pst.roots[le], pst.roots[ri]);
    }
    int query_impl(int k, int tl, int tr, int vl, int vr) const {
        if (tr - tl == 1) return tl;
        int tm = tl + (tr - tl) / 2;
        int left_count = int(pst.tree[pst.tree[vr].lch].sum - pst.tree[pst.tree[vl].lch].sum);
        if (left_count > k) return query_impl(k, tl, tm, pst.tree[vl].lch, pst.tree[vr].lch);
        return query_impl(k - left_count, tm, tr, pst.tree[vl].rch, pst.tree[vr].rch);
    }
};
