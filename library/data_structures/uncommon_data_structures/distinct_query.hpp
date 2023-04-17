/** @file */
#pragma once
/**
 * @see https://cp-algorithms.com/data_structures/segment_tree.html#
 *     preserving-the-history-of-its-values-persistent-segment-tree
 */
struct distinct_query {
    struct node {
        int sum;
        int lch, rch; /**< children, indexes into `tree` */
        node(int a_sum, int a_lch, int a_rch) : sum(a_sum), lch(a_lch), rch(a_rch) {}
    };
    const int N;
    vector<int> roots; /**< roots[i] corresponds to prefix arr[0, i) */
    deque<node> tree;
    /**
     * @param arr static array; can't handle updates
     * @time O(n log n)
     * @memory O(n log n)
     */
    distinct_query(const vector<int>& arr) : N(ssize(arr)), roots(N + 1) {
        tree.emplace_back(0, 0, 0); //acts as null
        map<int, int> last_idx;
        for (int i = 0; i < N; i++) {
            roots[i + 1] = update_impl(last_idx[arr[i]], 0, N, roots[i]);
            last_idx[arr[i]] = i + 1;
        }
    }
    int update_impl(int idx, int tl, int tr, int v) {
        if (tr - tl == 1) {
            tree.emplace_back(tree[v].sum + 1, 0, 0);
            return ssize(tree) - 1;
        }
        int tm = tl + (tr - tl) / 2;
        int lch = tree[v].lch;
        int rch = tree[v].rch;
        if (idx < tm)
            lch = update_impl(idx, tl, tm, lch);
        else
            rch = update_impl(idx, tm, tr, rch);
        tree.emplace_back(tree[lch].sum + tree[rch].sum, lch, rch);
        return ssize(tree) - 1;
    }
    /**
     * @param le,ri defines range [le, ri)
     * @returns number of distinct elements in range; query(i, i) returns 0.
     * @time O(log n)
     */
    int query(int le, int ri) const {
        assert(0 <= le && le <= ri && ri <= N);
        return query_impl(le + 1, 0, N, roots[le], roots[ri]);
    }
    int query_impl(int idx, int tl, int tr, int vl, int vr) const {
        if (tree[vr].sum == 0 || idx <= tl) return 0;
        if (tr <= idx) return tree[vr].sum - tree[vl].sum;
        int tm = tl + (tr - tl) / 2;
        return
            query_impl(idx, tl, tm, tree[vl].lch, tree[vr].lch) +
            query_impl(idx, tm, tr, tree[vl].rch, tree[vr].rch);
    }
};
