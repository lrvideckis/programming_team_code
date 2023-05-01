/** @file */
#pragma once
const int MOD = 998'244'353;
/**
 * @param a,b arrays of the same length, where the length is a power of 2
 * @returns array `c` where `c[k]` = the sum of (a[i] * b[j]) for all pairs
 * (i,j) where i & j == k
 * @time O(2^n * n)
 * @memory O(2^n)
 */
vector<int> and_convolution(vector<int> a, vector<int> b) {
    int n = __lg(ssize(a));
    assert(ssize(a) == ssize(b) && (1 << n) == ssize(a));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << n); j++) {
            if (!((j >> i) & 1)) {
                a[j] = (a[j] + a[j ^ (1 << i)]) % MOD;
                b[j] = (b[j] + b[j ^ (1 << i)]) % MOD;
            }
        }
    }
    vector<int> c(1 << n);
    for (int i = 0; i < (1 << n); i++)
        c[i] = 1LL * a[i] * b[i] % MOD;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < (1 << n); j++)
            if (!((j >> i) & 1))
                c[j] = (c[j] - c[j ^ (1 << i)] + MOD) % MOD;
    return c;
}
