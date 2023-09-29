/** @file */
#pragma once
template <class F> void quotients(long long n, F f) {
    for (long long le = 1, ri; le <= n; le = ri + 1) {
        ri = n / (n / le);
        /**
         * i-th iteration gives an interval [le_i, ri_i], we have:
         *     - for all i in [le_i, ri_i]: n / i has the same value
         *     - le_0 = 1
         *     - ri_last = n
         *     - ri_i + 1 = le_(i+1)
         */
        f(le, ri);
    }
}
