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
    vector<vector<array<int, 4>>> info;
    vector<array<pair<bit_rupq<T>, vector<int>>, 2>> bits;
    /**
     * @param adj unrooted, undirected tree
     * @param a_a a_a[u] = initial value for node u
     * @time O(n log1.5 n)
     * @space O(n log1.5 n) for `info` and `bits`
     */
    contour_range_update(const vector<vector<int>>& adj, const vector<T>& a_a) : n(ssize(a_a)), a(a_a), sum_par(n), sum_ch(n), par(n, -1), info(n) {
        edge_cd(adj, [&](const vector<vector<int>>& cd_adj, int cent, int split) -> void {
            queue<array<int, 4>> q;
            for (int i = 0; i < ssize(cd_adj[cent]); i++)
                q.push({cd_adj[cent][i], cent, 1, i < split});
            vector<vector<int>> d_to_in(2, vector<int>(1, -1));
            array<int, 2> siz = {0, 0};
            while (!empty(q)) {
                auto [u, p, d, side] = q.front();
                q.pop();
                if (ssize(d_to_in[side]) == d)
                    d_to_in[side].push_back(siz[side]);
                info[u].push_back({ssize(bits), d, siz[side]++, side});
                for (int v : cd_adj[u])
                    if (v != p) q.push({v, u, 1 + d, side});
            }
            for (int side = 0; side < 2; side++)
                d_to_in[side].push_back(siz[side]);
            bits.push_back({pair(bit_rupq<T>(siz[0]), d_to_in[0]),
                            pair(bit_rupq<T>(siz[1]), d_to_in[1])});
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
        for (auto [decomp_id, d, _, side] : info[u]) {
            auto& [bit, to_in] = bits[decomp_id][!side];
            int my_l = to_in[clamp<int>(le - d, 1, ssize(to_in) - 1)];
            int my_r = to_in[clamp<int>(ri - d, 1, ssize(to_in) - 1)];
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
        for (auto [decomp_id, _, time_in, side] : info[u])
            sum += bits[decomp_id][side].first.get_index(time_in);
        return sum;
    }
};
