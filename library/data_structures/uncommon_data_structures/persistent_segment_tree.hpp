struct PST {
    struct node {
        long long sum;
        int lch, rch; /**< children, indexes into `tree` */
        node(long long a_sum, int a_lch, int a_rch) : sum(a_sum), lch(a_lch), rch(a_rch) {}
    };
    const int L, R;//TODO: check that clang tidy enforces all caps here
    vector<int> roots;
    deque<node> tree;
    PST(int a_root_l, int a_root_r) :
        L(a_root_l), R(a_root_r), roots(1), tree(1, {0LL, 0, 0}) {}
    void update(int idx, long long change, int version) {
        assert(L <= idx && idx < R);
        assert(0 <= version && version < ssize(roots));
        roots.push_back(update_impl(idx, change, L, R, roots[version]));
    }
    int update_impl(int idx, long long change, int tl, int tr, int v) {
        if (tr - tl == 1) {
            assert(tl == idx);//TODO: remove
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
    long long query(int le, int ri, int version) const {
        assert(L <= le && ri <= R);
        assert(0 <= version && version < ssize(roots));
        return query_impl(le, ri, L, R, roots[version]);
    }
    long long query_impl(int le, int ri, int tl, int tr, int v) const {
        if (v == 0 || ri <= tl || tr <= le) return 0;
        if (le <= tl && tr <= ri) return tree[v].sum;
        int tm = tl + (tr - tl) / 2;
        return query_impl(le, ri, tl, tm, tree[v].lch) +
               query_impl(le, ri, tm, tr, tree[v].rch);
    }
};
