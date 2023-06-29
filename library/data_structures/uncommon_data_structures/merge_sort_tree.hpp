/** @file */
#pragma once

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
    vector<vector<int>> tree, num_went_left/*TODO: rename*/;
    /**
     * @param arr static array
     * @time O(n log n)
     * @space O(n log n) for `tree` vector
     */
    merge_sort_tree(const vector<int>& arr) : N(ssize(arr)), tree(2 * N), num_went_left(N) {
        transform(begin(arr), end(arr), begin(tree) + N, [](int val) -> vector<int> {return {val};});
        rotate(begin(tree) + N, begin(tree) + (N ? 3 * N - (2 << __lg(N)) : 0), end(tree));
        for (int i = N - 1; i >= 1; i--) {
            const auto& le = tree[2 * i];
            const auto& ri = tree[2 * i + 1];
            vector<pair<int, bool>> both(ssize(le) + ssize(ri));
            transform(begin(le), end(le), begin(both), [](int val) {return pair(val, 1);});
            transform(begin(ri), end(ri), begin(both) + ssize(le), [](int val) {return pair(val, 0);});
            inplace_merge(begin(both), begin(both) + ssize(le), end(both));
            tree[i].resize(ssize(both));
            transform(begin(both), end(both), begin(tree[i]), [](auto val) {return val.first;});
            num_went_left[i].resize(ssize(both) + 1);
            transform_inclusive_scan(begin(both), end(both), begin(num_went_left[i]) + 1, plus{}, [](auto val) {return int(val.second);});
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
        int tm = split_2(tl, tr), pl = num_went_left[v][xi], pr = num_went_left[v][yi];
        return query_impl(le, ri, pl, pr, tl, tm, 2 * v) +
               query_impl(le, ri, xi - pl, yi - pr, tm, tr, 2 * v + 1);
    }
};
