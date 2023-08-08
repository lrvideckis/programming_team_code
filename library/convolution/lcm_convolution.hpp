/** @file */
#pragma once
const int mod = 998'244'353;
/**
 * @param a,b arrays of the same length
 * @returns array `c` where `c[k]` = the sum of (a[i] * b[j]) for all pairs
 * (i,j) where lcm(i,j) == k
 * @time O(n log n)
 * @space this function allocates/returns various O(n) vectors
 */
vector<int> lcm_convolution(const vector<int>& a, const vector<int>& b) {
    assert(ssize(a) == ssize(b));
    int n = ssize(a);
    vector<long long> sum_a(n), sum_b(n);
    vector<int> c(n);
    for (int i = 1; i < n; i++) {
        for (int j = i; j < n; j += i)
            sum_a[j] += a[i], sum_b[j] += b[i];
        sum_a[i] %= mod, sum_b[i] %= mod;
        c[i] = int((c[i] + sum_a[i] * sum_b[i]) % mod);
        for (int j = i + i; j < n; j += i)
            if ((c[j] -= c[i]) < 0) c[j] += mod;
    }
    return c;
}
