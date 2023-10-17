/** @file */
#pragma once
template <class T> vector<vector<int>> lcs_dp(const T& s, const T& t) {
    auto n = ssize(s), m = ssize(t);
    vector h(n + 1, vector(m + 1, 0));
    iota(begin(h[0]), end(h[0]), 0);
    for (int i = 1; i <= n; i++)
        for (int j = 1, v = 0; j <= m; j++) {
            h[i][j] = v, v = h[i - 1][j];
            if (s[i - 1] != t[j - 1] && v > h[i][j]) swap(v, h[i][j]);
        }
    return h;
}
