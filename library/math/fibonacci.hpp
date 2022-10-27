#pragma once
//https://codeforces.com/blog/entry/14516
//O(log(n))
unordered_map<long long, long long> table;
long long fib(long long n, long long mod) {
	if (n < 2)
		return 1;
	if (table.find(n) != table.end())
		return table[n];
	table[n] = (fib((n + 1) / 2, mod) * fib(n / 2, mod) + fib((n - 1) / 2, mod) * fib((n - 2) / 2, mod)) % mod;
	return table[n];
}
