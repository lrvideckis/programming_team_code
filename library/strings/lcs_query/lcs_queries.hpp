/** @file */
#pragma once
#include "../../data_structures/binary_indexed_tree/range_update_point_query.hpp"
#include "lcs_dp.hpp"
vector<int> lcs_queries(const vector<vector<int>>& h, const vector<array<int, 3>>& queries) {
    auto n = ssize(h) - 1, m = ssize(h[0]) - 1, q = ssize(queries);
    vector qs(n + 1, vector(m + 1, vector<array<int, 2>>()));
    for (int i = 0; i < q; i++) {
        auto [a, b, c] = queries[i];
        assert(0 <= a && a <= n);
        assert(0 <= b && b <= c && c <= m);
        qs[a][c].push_back({b, i});
    }
    vector<int> res(q);
    for (int i = 0; i <= n; i++) {
        bit_rupq<int> bit(m);
        for (int j = 0; j <= m; j++) {
            //if (j) {
                assert(h[i][j] <= j);
                assert(j <= m);
                assert(h[i][j] >= 0);
                bit.update(h[i][j], j, 1);
                //bit.update(h[i][j], 1); //TODO: switch to range update, point query BIT
                //bit.update(j, -1);
            //}
            for (auto [le, idx] : qs[i][j]) {
                assert(0 <= le && le <= m);
                res[idx] = (le == m ? 0 : bit.get_index(le));
            }
        }
    }
    return res;
}
