/** @file */
#pragma once
#include "../../data_structures/binary_indexed_tree/bit.hpp"
#include "lcs_dp.hpp"
template <class T> vector<int> lcs_queries(const T& s, const T& t, const vector<array<int, 3>>& queries) {
    auto n = ssize(s), m = ssize(t), q = ssize(queries);
    vector qs(n, vector(m, vector<array<int, 2>>()));
    for (int i = 0; i < q; i++) {
        auto [s_ri, t_le, t_ri] = queries[i];
        assert(0 <= s_ri && s_ri <= n);
        assert(0 <= t_le && t_le <= t_ri && t_ri <= m);
        if (s_ri == 0 || t_le == m) continue;
        qs[s_ri - 1][t_le].push_back({t_ri, i});
    }
    lcs_dp lcs(t);
    vector<int> res(q);
    for (int i = 0; i < n; i++) {
        lcs.push_onto_s(s[i]);
        vector<int> init(m), dp_inv(m, -1);
        for (int j = 0; j < m; j++) {
            if (lcs.dp[j] == -1) init[j] = 1;
            else dp_inv[lcs.dp[j]] = j;
        }
        BIT<int> bit(init);
        for (int t_le = 0; t_le < m; t_le++) {
            for (auto [t_ri, idx] : qs[i][t_le])
                res[idx] = bit.sum(t_le, t_ri);
            if (dp_inv[t_le] != -1) bit.update(dp_inv[t_le], 1);
        }
    }
    return res;
}
