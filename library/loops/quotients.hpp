/** @file */
#pragma once
template <class F> void quotients(long long n, F f) {
    for (long long l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        // n / i has the same value for l <= i <= r
        f(n / l);
    }
}
