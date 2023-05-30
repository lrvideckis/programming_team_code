/** @file */
#pragma once
const int MOD = 998'244'353;
/**
 * @see https://codeforces.com/blog/entry/14516 https://cp-algorithms.com/algebra/fibonacci-numbers.html#fast-doubling-method
 * @code{.cpp}
 *     auto val = fib(n).first;
 *     //n=0 -> val=0
 *     //n=1 -> val=1
 *     //n=2 -> val=1
 *     //n=3 -> val=2
 *     //n=4 -> val=3
 *     //n=5 -> val=5
 * @endcode
 * @param n an integer
 * @returns a pair {nth fibonacci number, (n+1)th fibonacci number}
 * @time O(log n)
 */
pair<long long, long long> fib(long long n) {
    if (n == 0) return {0LL, 1LL};
    auto [x, y] = fib(n >> 1);
    long long c = x * (2 * y - x + MOD) % MOD, d = (x * x + y * y) % MOD;
    if (n & 1) return {d, (c + d) % MOD};
    return {c, d};
}
