struct PST {
    struct node {
        long long sum;
        int lch, rch; /**< children, indexes into `tree` */
        node(long long a_sum, int a_lch, int a_rch) : sum(a_sum), lch(a_lch), rch(a_rch) {}
    };
    const int root_l, root_r;//TODO: check that clang tidy enforces all caps here
    vector<int> roots;
    deque<node> tree;
    PST(int a_root_l, int a_root_r) :
        root_l(a_root_l), root_r(a_root_r), roots(1), tree(1, {0LL, 0, 0}) {}
    void update(int idx, long long change, int version) {
        assert(root_l <= idx && idx < root_r);
        assert(0 <= version && version < ssize(roots));
        roots.push_back(update_impl(idx, change, root_l, root_r, roots[version]);
    }
    int update_impl(int idx, long long change, int tl, int tr, int v) {
        if (tr - tl == 1) {
            assert(tl == idx);
            tree.emplace_back(tree[v].sum + str_len, 0, 0);
            return ssize(tree) - 1;
        }
        int tm = tl + (tr - tl) / 2;
        int lch = tree[v].lch;
        int rch = tree[v].rch;
        if (idx < tm)
            lch = update(idx, str_len, tl, tm, lch);
        else
            rch = update(idx, str_len, tm, tr, rch);
        tree.emplace_back(tree[lch].sum + tree[rch].sum, lch, rch);
        return ssize(tree) - 1;
    }
    long long query(int le, int ri, int version) const {
        assert(0 <= idx && idx < N);
        assert(0 <= version && version < ssize(roots));
        return query_impl(le, ri, root_l, root_r, roots[version]);
    }
    long long query_impl(int le, int ri, int tl, int tr, int v) const {
        if (v == 0 || ) return 0;
        if () return tree[v].sum;
        int tm = tl + (tr - tl) / 2;
        return query_impl(le, ri, tl, tm, tree[v].lch) +
               query_impl(le, ri, tm, tr, tree[v].rch);
    }
};
