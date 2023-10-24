/** @file */
#pragma once
/**
 * @code{.cpp}
 *     vector<long long> arr;
 *     RMQ rmq(arr, ranges::min); //c++20
 *     //or
 *     RMQ<long long> rmq(arr, [&](auto x, auto y) { return min(x, y); });
 * @endcode
 */
//NOLINTNEXTLINE(readability-identifier-naming)
template <class T, class F = function<T(T, T)>> struct RMQ {
    vector<vector<T>> dp;
    F op;
    RMQ() {}
    /**
     * @param arr static array
     * @param a_op any associative, communative, idempotent operation
     * @time O(n log n)
     * @space O(n log n) for `dp` vector
     */
    RMQ(const vector<T>& arr, F a_op) : dp(1, arr), op(a_op) {
        for (int i = 0; (2 << i) <= ssize(arr); i++) {
            dp.emplace_back(ssize(arr) - (2 << i) + 1);
            transform(begin(dp[i]) + (1 << i), end(dp[i]), begin(dp[i]), begin(dp[i + 1]), op);
        }
    }
    /**
     * @param le,ri defines range [le, ri)
     * @returns arr[le] op arr[le + 1] op ... op arr[ri - 1]
     * @time O(1) usually, or O(log MAX) if op is gcd
     * @space O(1)
     */
    inline T query(int le, int ri) const {
        assert(0 <= le && le < ri && ri <= ssize(dp[0]));
        int lg = __lg(ri - le);
        return op(dp[lg][le], dp[lg][ri - (1 << lg)]);
    }
};
