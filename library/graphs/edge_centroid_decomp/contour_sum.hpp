/** @file */
#pragma once
#include "../../data_structures/bit.hpp"
#include "edge_cd.hpp"
/**
 * @see https://judge.yosupo.jp/problem /vertex_add_range_contour_sum_on_tree
 */
template <class T> struct contour_sum {
    int n;
    vector<T> a, sum_ch;
    vector<int> par;
    vector<vector<array<int, 3>>> info;
    vector<array<BIT<T>, 2>> bits;
    /**
     * @param adj unrooted, undirected tree
     * @param a_a a_a[u] = initial value for node u
     * @time O(n log1.5 n)
     * @space O(n log1.5 n) for `info` and `bits`
     */
    contour_sum(const vector<vector<int>>& adj, const vector<T>& a_a) : n(ssize(a_a)), a(a_a), sum_ch(n), par(n, -1), info(n) {
        edge_cd(adj, [&](const vector<vector<int>>& cd_adj, int cent, int split) -> void {
            vector<vector<T>> sum_val(2, vector<T>(1));
            auto dfs = [&](auto&& self, int u, int p, int d, int side) -> void {
                info[u].push_back({ssize(bits), d, side});
                if (ssize(sum_val[side]) == d) sum_val[side].push_back(0);
                sum_val[side][d] += a[u];
                for (int v : cd_adj[u])
                    if (v != p) self(self, v, u, 1 + d, side);
            };
            for (int i = 0; i < ssize(cd_adj[cent]); i++)
                dfs(dfs, cd_adj[cent][i], cent, 1, i < split);
            bits.push_back({BIT<T>(sum_val[0]), BIT<T>(sum_val[1])});
        });
        auto dfs = [&](auto&& self, int u) -> void {
            for (int v : adj[u])
                if (v != par[u])
                    par[v] = u, sum_ch[u] += a[v], self(self, v);
        };
        dfs(dfs, 0);
    }
    /**
     * @param u node
     * @param delta value to add to node u's value
     * @time O(log1.5(n) * log2(n))
     * @space O(1)
     */
    void update(int u, T delta) {
        a[u] += delta;
        if (par[u] != -1) sum_ch[par[u]] += delta;
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
        if (le <= 0 && 0 < ri) sum += a[u];
        if (le <= 1 && 1 < ri) sum += sum_ch[u] + (par[u] != -1 ? a[par[u]] : 0);
        for (auto [decomp, d, side] : info[u]) {
            auto& bit = bits[decomp][!side];
            int my_l = clamp<int>(le - d, 1, ssize(bit.s));
            int my_r = clamp<int>(ri - d, 1, ssize(bit.s));
            sum += bit.sum(my_l, my_r);
        }
        return sum;
    }
};
