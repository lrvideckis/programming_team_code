/** @file */
#pragma once
#include "bit_presum.hpp"
inline int split_2(int tl, int tr) {
    int pw2 = 1 << __lg(tr - tl);
    return min(tl + pw2, tr - pw2 / 2);
}
/**
 * For point updates: either switch to policy based BST, or use sqrt
 * decomposition.
 */
struct merge_sort_tree {
    const int N;
    vector<vector<int>> tree;
    vector<bit_presum> bit_presums;
    /**
     * @param arr static array
     * @time O(n log n)
     * @space O(n log n) for `tree` vector
     *        O((n log n) / 64) for `bit_presums` vector
     */
    merge_sort_tree(const vector<int>& arr) : N(ssize(arr)), tree(2 * N), bit_presums(N, vector<bool>()) {
        transform(begin(arr), end(arr), begin(tree) + N, [](int val) -> vector<int> {return {val};});
        rotate(begin(tree) + N, begin(tree) + (N ? 3 * N - (2 << __lg(N)) : 0), end(tree));
        vector<pair<int, bool>> both(N);
        for (int i = N - 1; i >= 1; i--) {
            const auto& le = tree[2 * i];
            const auto& ri = tree[2 * i + 1];
            int tot = ssize(le) + ssize(ri);
            transform(begin(le), end(le), begin(both), [](int val) {return pair(val, 1);});
            transform(begin(ri), end(ri), begin(both) + ssize(le), [](int val) {return pair(val, 0);});
            inplace_merge(begin(both), begin(both) + ssize(le), begin(both) + tot);
            tree[i].resize(tot);
            vector<bool> bits(tot);
            transform(begin(both), begin(both) + tot, begin(tree[i]), [](auto val) {return val.first;});
            transform(begin(both), begin(both) + tot, begin(bits), [](auto val) {return val.second;});
            bit_presums[i] = bit_presum(bits);
        }
    }
    int query(int le, int ri, int x, int y) const {
        int xi = int(lower_bound(begin(tree[1]), end(tree[1]), x) - begin(tree[1]));
        int yi = int(lower_bound(begin(tree[1]), end(tree[1]), y) - begin(tree[1]));
        return query_impl(le, ri, xi, yi, 0, N, 1);
    }
    int query_impl(int le, int ri, int xi, int yi, int tl, int tr, int v) const {
        if (ri <= tl || tr <= le) return 0;
        if (le <= tl && tr <= ri) return yi - xi;
        int tm = split_2(tl, tr), pl = bit_presums[v].popcount(xi), pr = bit_presums[v].popcount(yi);
        return query_impl(le, ri, pl, pr, tl, tm, 2 * v) +
               query_impl(le, ri, xi - pl, yi - pr, tm, tr, 2 * v + 1);
    }
};
