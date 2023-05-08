/** @file */
#pragma once
const int MOD = 998'244'353;
unordered_map<long long, long long> table; /**< for memoization */
/**
 * @see https://codeforces.com/blog/entry/14516
 * @param n an integer
 * @returns nth fibonacci number
 * @time O(log n)
 * @space O(log n)
 */
long long fib(long long n) {
    if (n < 2) return 1;
    if (table.find(n) != end(table)) return table[n];
    table[n] = (fib((n + 1) / 2) * fib(n / 2) + fib((n - 1) / 2) * fib((n - 2) / 2)) % MOD;
    return table[n];
}
