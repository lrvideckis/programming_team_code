#pragma once

//status: not tested
//https://codeforces.com/blog/entry/14516

const int mod = 1e9 + 7;
unordered_map<int, int> table;
int fib(int n) {    //**O(log(n))**
	if (n < 2) return 1;
	if (table.find(n) != table.end()) return table[n];
	table[n] = (1LL * fib((n + 1) / 2) * fib(n / 2) + 1LL * fib((n - 1) / 2) * fib((n - 2) / 2)) % mod;
	return table[n];
}
