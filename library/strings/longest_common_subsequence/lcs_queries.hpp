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
        //if (s_ri == 0 || t_le == m) continue;
        qs[s_ri - 1][t_le].push_back({t_ri, i});
    }
    lcs_dp lcs(t);
    for(int i = 0; i < n; i++) {
        lcs.push_onto_s(s[i]);
        // queries of given [t_le, t_ri): find number of indexes i such that t_le <= i < t_ri && lcs.dp[i] < t_le
        BIT<int> bit{int(m)};

    }
    return res;
}
