/** @file */
#pragma once
#include "../../../kactl/content/data-structures/UnionFind.h"
#include "../../monotonic_stack/monotonic_stack.hpp"
/**
 * @see https://codeforces.com/blog/entry/78898
 * @code{.cpp}
       auto [is_join, mn_idx, mn_val, len, root, adj] = perm_tree(a);
 * @endcode
 */
struct perm_tree {
    vector<bool> is_join;
    /**
     * [mn_idx[u], mn_idx[u] + len[u]) is range of indexes
     * [mn_val[u], mn_val[u] + len[u]) is range of values
     * @{
     */
    vector<int> mn_idx, mn_val, len;
    /** @} */
    int root;
    vector<vector<int>> adj;  /**< [0, n) are leaves, [n, ssize(adj)) are internal nodes */
    bool touches(int u, int v) {
        return mn_val[u] == mn_val[v] + len[v] || mn_val[v] == mn_val[u] + len[u];
    }
    int allocate(bool join, int mn_i, int mn_v, int ln, const vector<int>& ch) {
        int u = ssize(adj);
        is_join.push_back(join);
        mn_idx.push_back(mn_i);
        mn_val.push_back(mn_v);
        len.push_back(ln);
        adj.push_back(ch);
        return u;
    }
    /**
     * @param a permutation
     * @time O(n * α(n))
     * @space O(n)
     */
    perm_tree(const vector<int>& a) {
        int n = ssize(a);
        vector<int> mn_i(n), mx_i(n);
        {
            vector<int> a_inv(n, -1), qr(n);
            for (int i = 0; i < n; i++) {
                assert(0 <= a[i] && a[i] < n && a_inv[a[i]] == -1);
                a_inv[a[i]] = i;
            }
            vector least(2, vector(n, 0)), ri = {mono_st(a_inv, less()), mono_st(a_inv, greater())};
            vector<vector<int>> qi(n);
            for (int i = 1; i < n; i++) {
                auto [x, y] = minmax(a[i - 1], a[i]);
                qr[i] = y;
                qi[x].push_back(i);
                least[0][i] = least[1][i] = i;
            }
            array<UF, 2> uf = {UF(n), UF(n)};
            for (int i = n - 1; i >= 0; i--) {
                for (int j = 0; j < 2; j++) {
                    for (int k = i + 1; k != ri[j][i]; k = ri[j][k]) uf[j].join(i, k);
                    least[j][uf[j].find(i)] = i;
                }
                for (int idx : qi[i]) {
                    mn_i[idx] = a_inv[least[0][uf[0].find(qr[idx])]];
                    mx_i[idx] = a_inv[least[1][uf[1].find(qr[idx])]];
                }
            }
        }
        for (int i = 0; i < n; i++) allocate(1, i, a[i], 1, {});
        vector<array<int, 4>> st;
        for (int i = 0; i < n; i++) {
            int u = i;
            while (!empty(st)) {
                int v = st.back()[0];
                if (!empty(adj[v]) && touches(adj[v].back(), u)) {
                    mn_val[v] = min(mn_val[v], mn_val[u]);
                    len[v] += len[u];
                    adj[v].push_back(u);
                    u = v;
                    st.pop_back();
                    continue;
                }
                if (touches(u, v)) {
                    u = allocate(1, mn_idx[v], min(mn_val[u], mn_val[v]), len[u] + len[v], {v, u});
                    st.pop_back();
                    continue;
                }
                int le = min(mn_idx[v], mn_i[mn_idx[u]]), ri = max(i, mx_i[mn_idx[u]]), idx = ssize(st) - 1;
                while (ri == i && le != mn_idx[st[idx][0]])
                    le = min(le, st[idx][1]), ri = max(ri, st[idx][2]), idx = st[idx][3];
                if (ri > i) {
                    st.push_back({u, le, ri, idx});
                    break;
                }
                int min_val = mn_val[u];
                vector<int> ch(1 + ssize(st) - idx, u);
                for (int j = idx; j < ssize(st); j++)
                    min_val = min(min_val, mn_val[ch[j - idx] = st[j][0]]);
                u = allocate(0, le, min_val, i - le + 1, ch);
                st.resize(idx);
            }
            if (empty(st)) st.push_back({u, -1, -1, -1});
        }
        assert(ssize(st) == 1);
        root = st[0][0];
    }
};
