/** @file */
#pragma once
#include "persistent_segment_tree.hpp"
/**
 * @see https://cp-algorithms.com/data_structures/segment_tree.html#
 *     preserving-the-history-of-its-values-persistent-segment-tree
 */
struct distinct_query {
    const int N;
    PST pst;
    /**
     * @param arr static array; can't handle updates
     * @time O(n log n)
     * @space O(n log n)
     */
    distinct_query(const vector<int>& arr) : N(ssize(arr)), pst(0, N + 1) {
        map<int, int> last_idx;
        for (int i = 0; i < N; i++) {
            int& idx = last_idx[arr[i]];
            pst.update(idx, 1, i);
            idx = i + 1;
        }
    }
    /**
     * @param le,ri defines range [le, ri)
     * @returns number of distinct elements in range; query(i, i) returns 0.
     * @time O(log n)
     */
    int query(int le, int ri) const {
        assert(0 <= le && le <= ri && ri <= N);
        return pst.query(0, le + 1, ri) - pst.query(0, le + 1, le);
    }
};
