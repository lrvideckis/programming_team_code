/** @file */
#pragma once
const int MOD = 1'000'000'007;
unordered_map<long long, long long> table; /**< for memoization */
/**
 * @see https://codeforces.com/blog/entry/14516
 * @param n an integer
 * @returns nth fibonacci number
 * @time O(log n)
 */
long long fib(long long n) {
    if (n < 2) return 1;
    if (table.find(n) != table.end()) return table[n];
    table[n] = (fib((n + 1) / 2) * fib(n / 2) + fib((n - 1) / 2) * fib((n - 2) / 2)) % MOD;
    return table[n];
}
