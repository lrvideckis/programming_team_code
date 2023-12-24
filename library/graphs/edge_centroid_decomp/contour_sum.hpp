/** @file */
#pragma once
#include "../../data_structures/bit.hpp"
#include "edge_cd.hpp"
/**
 * @see https://judge.yosupo.jp/problem/vertex_add_range_contour_sum_on_tree
 *
 * Note for edge centroid decomp you need to special case single-edge paths.
 * I do this by BIT over pre order BFS traversal
 */
template <class T> struct contour_sum {
    vector<vector<int>> adj;
    int n;
    vector<T> a;
    vector<vector<array<int, 3>>> info;
    vector<array<BIT<T>, 2>> bits;
    vector<int> in, in_ch, par;
    BIT<T> order;
    /**
     * @param a_adj unrooted, undirected tree
     * @param a_a a_a[u] = initial value for node u
     * @time O(n log1.5 n)
     * @space O(n log1.5 n) for `info` and `bits`
     */
    contour_sum(const vector<vector<int>>& a_adj, const vector<T>& a_a) : adj(a_adj), n(ssize(a_a)), a(a_a), info(n), in(n), in_ch(n, -1), par(n) {
        edge_cd(adj, [&](const vector<vector<int>>& adj_cd, int cent, int split) -> void {
            vector<vector<T>> sum_val(2, vector<T>(1));
            auto dfs = [&](auto&& self, int u, int p, int d, int side) -> void {
                info[u].push_back({ssize(bits), d, side});
                if (ssize(sum_val[side]) == d) sum_val[side].push_back(0);
                sum_val[side][d] += a[u];
                for (int v : adj_cd[u])
                    if (v != p) self(self, v, u, 1 + d, side);
            };
            for (int i = 0; i < ssize(adj_cd[cent]); i++)
                dfs(dfs, adj_cd[cent][i], cent, 1, i < split);
            bits.push_back({BIT<T>(sum_val[0]), BIT<T>(sum_val[1])});
        });
        queue<array<int, 2>> q({{0, -1}});
        vector<T> init;
        while (!empty(q)) {
            auto [u, p] = q.front();
            q.pop();
            par[u] = p;
            if (p != -1 && in_ch[p] == -1) in_ch[p] = ssize(init);
            in[u] = ssize(init);
            init.push_back(a[u]);
            for (int v : adj[u])
                if (v != p) q.push({v, u});
        }
        order = {init};
    }
    /**
     * @param u node
     * @param delta value to add to node u's value
     * @time O(log1.5(n) * log2(n))
     * @space O(1)
     */
    void update(int u, T delta) {
        a[u] += delta;
        order.update(in[u], delta);
        for (auto [decomp, d, side] : info[u])
            bits[decomp][side].update(d, delta);
    }
    /**
     * @param u node
     * @param le,ri defines range [le, ri)
     * @returns sum of node v's value over all v such that le <= dist_edges(u, v) < ri
     * @time O(log1.5(n) * log2(n))
     * @space O(1)
     */
    T query(int u, int le, int ri) {
        T sum = 0;
        if (le == 0) sum += a[u];
        if (le <= 1 && 1 < ri) {
            if (par[u] != -1) sum += a[par[u]];
            if (in_ch[u] != -1) sum += order.sum(in_ch[u], in_ch[u] + ssize(adj[u]) - (par[u] != -1));
        }
        for (auto [decomp, d, side] : info[u]) {
            auto& bit = bits[decomp][!side];
            int my_l = clamp<int>(le - d, 1, ssize(bit.s)), my_r = clamp<int>(ri - d, 1, ssize(bit.s));
            sum += bit.sum(my_l, my_r);
        }
        return sum;
    }
};
