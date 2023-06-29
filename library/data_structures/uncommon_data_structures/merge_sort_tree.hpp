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
    merge_sort_tree(const vector<int>& arr) : N(ssize(arr)), tree(2 * N), num_went_left(N, vector<int>(1)) {
        transform(begin(arr), end(arr), begin(tree) + N, [](int val) -> vector<int> {return {val};});
        rotate(begin(tree) + N, begin(tree) + (N ? 3 * N - (2 << __lg(N)) : 0), end(tree));
        for (int i = N - 1; i >= 1; i--) {
            const auto& le = tree[2 * i];
            const auto& ri = tree[2 * i + 1];
            //TODO: golf this: change tree to vector<vector<pair<int, int>>> maybe?
            //well no cuz we want num_went_left to be only length N
            int ptrL = 0, ptrR = 0;
            while(ptrL < ssize(le) && ptrR < ssize(ri)) {
                if(le[ptrL] < ri[ptrR]) {
                    tree[i].push_back(le[ptrL++]);
                    num_went_left[i].push_back(num_went_left[i].back() + 1);
                } else {
                    tree[i].push_back(ri[ptrR++]);
                    num_went_left[i].push_back(num_went_left[i].back());
                }
            }
            while(ptrL < ssize(le)) {
                tree[i].push_back(le[ptrL++]);
                num_went_left[i].push_back(num_went_left[i].back() + 1);
            }
            while(ptrR < ssize(ri)) {
                tree[i].push_back(ri[ptrR++]);
                num_went_left[i].push_back(num_went_left[i].back());
            }

            //tree[i].resize(ssize(le) + ssize(ri));
            //merge(begin(le), end(le), begin(ri), end(ri), begin(tree[i]));
        }
    }
    int query(int le, int ri, int x, int y) const {
        int xi = int(lower_bound(begin(tree[1]), end(tree[1]), x) - begin(tree[1]));
        int yi = int(lower_bound(begin(tree[1]), end(tree[1]), y) - begin(tree[1]));
        return query_impl(le, ri, xi, yi, 0, N, 1);
    }
    int query_impl(int le, int ri, int xi, int yi, int tl, int tr, int v) const {
        if (ri <= tl || tr <= le) return 0;
        //invariant: all values in subarray [xi, yi) in tree[v] are in range [x, y)
        if (le <= tl && tr <= ri) return yi - xi;
        int tm = split_2(tl, tr);
        int pl = num_went_left[v][xi], pr = num_went_left[v][yi];
        return query_impl(le, ri, pl, pr, tl, tm, 2 * v) +
               query_impl(le, ri, xi - pl, yi - pr, tm, tr, 2 * v + 1);
    }
};
