/** @file */
#pragma once
/**
 * @see https://codeforces.com/blog/entry/87940
 *
 * Disjoint RMQ is like normal RMQ except the 2 query ranges never overlap.
 * @code{.cpp}
 *     //usage for min and # of mins:
 *     vector<pair<long long, int>> arr; //initialize arr[i].second = 1
 *     disjoint_rmq<pair<long long, int>> rmq(arr, [&](auto x, auto y) {
 *         if (x.first == y.first) return make_pair(x.first, x.second + y.second);
 *         return min(x, y);
 *     });
 * @endcode
 */
template <typename T, typename F = function<T(const T&, const T&)>> struct disjoint_rmq {
    const int N;
    vector<vector<T>> dp;
    /**
     * examples:
     * - min and # of mins.
     * - product under composite mod
     * - matrix multiply
     * - function composition
     */
    F op;
    /**
     * @param arr static array
     * @param a_op any associative operation
     * @time O(n log n)
     * @space O(n log n) for `dp`
     */
    disjoint_rmq(const vector<T>& arr, const F& a_op) : N(ssize(arr)), op(a_op) {
        for (int len = 1; len <= N; len *= 2) {
            dp.emplace_back(N);
            for (int le = 0; le < N; le += 2 * len) {
                int mi = min(N, le + len), ri = min(N, le + 2 * len);
                partial_sum(rend(arr) - mi, rend(arr) - le, rend(dp.back()) - mi, [&](const T & x, const T & y) {return op(y, x);});
                partial_sum(begin(arr) + mi, begin(arr) + ri, begin(dp.back()) + mi, op);
            }
        }
    }
    /**
     * @param le,ri defines range [le, ri)
     * @returns op of range
     * @time O(1)
     * @space O(1)
     */
    inline T query(int le, int ri) const {
        assert(0 <= le && le < ri && ri <= N);
        if (ri - le == 1) return dp[0][le];
        int lg = __lg(le ^ (ri - 1));
        return op(dp[lg][le], dp[lg][ri - 1]);
    }
};
