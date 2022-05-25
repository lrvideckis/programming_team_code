#pragma once

//status: not tested
//https://codeforces.com/blog/entry/14516

unordered_map<long long, int> table;
int fib(long long n, int mod) {    //**O(log(n))**
	if (n < 2) return 1;
	if (table.find(n) != table.end()) return table[n];
	table[n] = (1LL * fib((n + 1) / 2, mod) * fib(n / 2, mod) + 1LL * fib((n - 1) / 2, mod) * fib((n - 2) / 2, mod)) % mod;
	return table[n];
}
