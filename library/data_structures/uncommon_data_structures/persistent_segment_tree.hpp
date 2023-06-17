/** @file */
#pragma once
/**
 * @see https://cp-algorithms.com/data_structures/segment_tree.html
 *     preserving-the-history-of-its-values-persistent-segment-tree
 */
//NOLINTNEXTLINE(readability-identifier-naming)
struct PST {
    struct node {
        long long sum;
        int lch, rch; /**< children, indexes into `tree` */
        node(long long a_sum, int a_lch, int a_rch) : sum(a_sum), lch(a_lch), rch(a_rch) {}
    };
    const int ROOT_L, ROOT_R;
    vector<int> roots; /**< tree[roots[i]] = root node at version i */
    deque<node> tree;
    /**
     * @param root_l,root_r defines range [ROOT_L, ROOT_L) of root node, can be
     * negative
     * @time O(1)
     * @space O(1)
     */
    PST(int root_l, int root_r) :
        ROOT_L(root_l), ROOT_R(root_r), roots(1), tree(1, {0LL, 0, 0}) {}
    /**
     * @param idx,change does arr[idx] += change
     * @param version which version to update. Each call to update creates a
     * new version. Initially there is a dummy version.
     * @time O(log(ROOT_R - ROOT_L))
     * @space O(log(ROOT_R - ROOT_L)) new nodes are pushed back onto `tree`; (and for recursion stack)
     */
    void update(int idx, long long change, int version) {
        assert(ROOT_L <= idx && idx < ROOT_R);
        assert(0 <= version && version < ssize(roots));
        roots.push_back(update_impl(idx, change, ROOT_L, ROOT_R, roots[version]));
    }
    int update_impl(int idx, long long change, int tl, int tr, int v) {
        if (tr - tl == 1) {
            tree.emplace_back(tree[v].sum + change, 0, 0);
            return ssize(tree) - 1;
        }
        int tm = tl + (tr - tl) / 2;
        int lch = tree[v].lch;
        int rch = tree[v].rch;
        if (idx < tm)
            lch = update_impl(idx, change, tl, tm, lch);
        else
            rch = update_impl(idx, change, tm, tr, rch);
        tree.emplace_back(tree[lch].sum + tree[rch].sum, lch, rch);
        return ssize(tree) - 1;
    }
    /**
     * @param le, ri defines range [le, ri)
     * @param version which version to query
     * @returns sum of range for that version
     * @time O(log(ROOT_R - ROOT_L))
     * @space O(log(ROOT_R - ROOT_L)) for recursion stack, no new nodes are allocated
     */
    long long query(int le, int ri, int version) const {
        assert(ROOT_L <= le && ri <= ROOT_R);
        assert(0 <= version && version < ssize(roots));
        return query_impl(le, ri, ROOT_L, ROOT_R, roots[version]);
    }
    long long query_impl(int le, int ri, int tl, int tr, int v) const {
        if (v == 0 || ri <= tl || tr <= le) return 0;
        if (le <= tl && tr <= ri) return tree[v].sum;
        int tm = tl + (tr - tl) / 2;
        return query_impl(le, ri, tl, tm, tree[v].lch) +
               query_impl(le, ri, tm, tr, tree[v].rch);
    }
};
