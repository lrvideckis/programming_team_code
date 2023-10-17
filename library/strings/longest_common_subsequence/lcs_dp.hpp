/** @file */
#pragma once
template <class T> struct lcs_dp {
    T t;
    vector<int> dp;
    lcs_dp(const T& a_t) : t(a_t), dp(ssize(t)) {
        iota(begin(dp), end(dp), 0);
    }
    void push_onto_s(int c) {
        for (int i = 0, v = -1; i < ssize(t); i++)
            if (c == t[i] || dp[i] < v) swap(dp[i], v);
    }
};
