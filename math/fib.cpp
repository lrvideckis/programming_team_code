unordered_map<ll,ll> table;
int fib(int n) {//**O(log(n))**
	if(n<2) return 1;
	if(table.find(n) != table.end()) return table[n];
	table[n] = (fib((n+1) / 2)*fib(n/2) + fib((n-1) / 2)*fib((n-2) / 2)) % mod;
	return table[n];
}
