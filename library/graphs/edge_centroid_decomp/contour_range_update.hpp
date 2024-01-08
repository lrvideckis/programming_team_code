/** @file */
#pragma once
#include "../../data_structures/bit_uncommon/rupq.hpp"
#include "edge_cd.hpp"
/**
 * @see https://judge.yosupo.jp/problem /vertex_get_range_contour_add_on_tree
 */
template <class T> struct contour_range_update {
    int n;
    vector<T> a, sum_par, sum_ch;
    vector<int> par;
    vector<vector<array<int, 3>>> info;
    vector<array<bit_rupq<T>, 2>> bits;
    /**
     * @param adj unrooted, undirected tree
     * @param _a _a[u] = initial value for node u
     * @time O(n log1.5 n)
     * @space O(n log1.5 n) for `info` and `bits`
     */
    contour_range_update(const vector<vector<int>>& adj, const vector<T>& _a) : n(ssize(_a)), a(_a), sum_par(n), sum_ch(n), par(n, -1), info(n) {
        edge_cd(adj, [&](const vector<vector<int>>& cd_adj, int cent, int split) {
            array<int, 2> mx_d = {0, 0};
            auto dfs = [&](auto&& self, int u, int p, int d, int side) -> void {
                mx_d[side] = max(mx_d[side], d);
                info[u].push_back({ssize(bits), d, side});
                for (int v : cd_adj[u])
                    if (v != p) self(self, v, u, 1 + d, side);
            };
            for (int i = 0; i < ssize(cd_adj[cent]); i++)
                dfs(dfs, cd_adj[cent][i], cent, 1, i < split);
            bits.push_back({bit_rupq<T>(mx_d[0] + 1), bit_rupq<T>(mx_d[1] + 1)});
        });
        auto dfs = [&](auto&& self, int u) -> void {
            for (int v : adj[u])
                if (v != par[u])
                    par[v] = u, self(self, v);
        };
        dfs(dfs, 0);
    }
    /**
     * @param u,le,ri,delta add delta to all nodes v such that le <= dist_edges(u, v) < ri
     * @time O(log1.5(n) * log2(n))
     * @space O(1)
     */
    void update(int u, int le, int ri, T delta) {
        assert(0 <= le && le <= ri && ri <= n);
        if (le <= 0 && 0 < ri) a[u] += delta;
        if (le <= 1 && 1 < ri) {
            sum_par[u] += delta;
            if (par[u] != -1) sum_ch[par[u]] += delta;
        }
        for (auto [decomp_id, d, side] : info[u]) {
            auto& bit = bits[decomp_id][!side];
            int my_l = clamp<int>(le - d, 1, bit.n);
            int my_r = clamp<int>(ri - d, 1, bit.n);
            bit.update(my_l, my_r, delta);
        }
    }
    /**
     * @param u node
     * @returns value of node u
     * @time O(log1.5(n) * log2(n))
     * @space O(1)
     */
    T query(int u) {
        T sum = a[u] + sum_ch[u] + (par[u] != -1 ? sum_par[par[u]] : 0);
        for (auto [decomp_id, d, side] : info[u])
            sum += bits[decomp_id][side].get_index(d);
        return sum;
    }
};
