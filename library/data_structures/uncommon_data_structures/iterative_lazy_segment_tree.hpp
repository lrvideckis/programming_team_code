/** @file */
#pragma once
#include "../lazy_segment_tree.hpp"
/**
 * @see https://codeforces.com/blog/entry/18051
 *
 * Iterative query and update functions access the exact same set of indexes as
 * their recursive counterparts.
 */
struct iter_seg_tree {
    const int S; /**< smallest power of 2 >= n */
    seg_tree st;
    iter_seg_tree(int n) : S(1 << __lg(2 * n - 1)), st(n) {}
    iter_seg_tree(const vector<long long>& arr) : S(1 << __lg(2 * ssize(arr) - 1)), st(arr) {}
    void pull(int v) {st.tree[v] = op(st.tree[2 * v], st.tree[2 * v + 1]);}
    /**
     * @see https://github.com/ecnerwala/cp-book/blob/master/src/seg_tree.hpp
     */
    int to_leaf(int i) const {
        i += S;
        return i < 2 * st.N ? i : 2 * (i - st.N);
    }
    /**
     * @see https://github.com/ecnerwala/cp-book/blob/master/src/seg_tree.hpp
     */
    pair<int, int> get_node_bounds(int a) const {
        assert(1 <= a && a < 2 * st.N);
        int l = __builtin_clz(a) - __builtin_clz(2 * st.N - 1);
        int x = a << l, y = (a + 1) << l;
        assert(S <= x && x < y && y <= 2 * S);
        return {(x >= 2 * st.N ? (x >> 1) + st.N : x) - S, (y >= 2 * st.N ? (y >> 1) + st.N : y) - S};
    }
    void push_parents(int le, int ri) {
        int lca_l_r = __lg((le - 1) ^ ri);
        for (int lg = __lg(le); lg > __builtin_ctz(le); lg--) {
            auto [tl, tr] = get_node_bounds(le >> lg);
            st.push(tl, split(tl, tr), tr, le >> lg);
        }
        for (int lg = lca_l_r; lg > __builtin_ctz(ri); lg--) {
            auto [tl, tr] = get_node_bounds(ri >> lg);
            st.push(tl, split(tl, tr), tr, ri >> lg);
        }
    }
    /**
     * @param le,ri defines range [le, ri)
     */
    void update_iter(int le, int ri, long long change) {
        assert(0 <= le && le <= ri && ri <= st.N);
        if (le == ri) return;
        le = to_leaf(le), ri = to_leaf(ri);
        push_parents(le, ri);
        for (int x = le, y = ri; x < y; x >>= 1, y >>= 1) {
            if (x & 1) {
                auto [tl, tr] = get_node_bounds(x);
                st.apply(change, tl, tr, x++);
            }
            if (y & 1) {
                auto [tl, tr] = get_node_bounds(--y);
                st.apply(change, tl, tr, y);
            }
        }
        int lca_l_r = __lg((le - 1) ^ ri);
        for (int lg = __builtin_ctz(ri) + 1; lg <= lca_l_r; lg++) pull(ri >> lg);
        for (int lg = __builtin_ctz(le) + 1; lg <= __lg(le); lg++) pull(le >> lg);
    }
    /**
     * @param le,ri defines range [le, ri)
     */
    long long query_iter(int le, int ri) {
        assert(0 <= le && le <= ri && ri <= st.N);
        if (le == ri) return 0;
        le = to_leaf(le), ri = to_leaf(ri);
        push_parents(le, ri);
        long long resl = 0, resr = 0;
        for (; le < ri; le >>= 1, ri >>= 1) {
            if (le & 1) resl = op(resl, st.tree[le++]);
            if (ri & 1) resr = op(st.tree[--ri], resr);
        }
        return op(resl, resr);
    }
};
