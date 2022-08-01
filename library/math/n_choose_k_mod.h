#pragma once
//for mod inverse
#include "exp_mod.h"
// usage:
//     n_choose_k nk(n, 1e9+7) to use `choose`, `inv` with inputs strictly < n
// or:
//     n_choose_k nk(mod, mod) to use `choose_with_lucas_theorem` with arbitrarily large inputs
struct n_choose_k {
	n_choose_k(int n, int a_mod) : mod(a_mod), fact(n, 1), inv_fact(n, 1) {
		//this implementation doesn't work if n > mod because n! % mod = 0 when n >= mod. So `inv_fact` array will be all 0's
		assert(max(n, 2) <= mod);
		//assert mod is prime. mod is intended to fit inside an int so that
		//multiplications fit in a longlong before being modded down. So this
		//will take sqrt(2^31) time
		for (int i = 2; i * i <= mod; i++) assert(mod % i);
		for (int i = 2; i < n; i++)
			fact[i] = 1LL * fact[i - 1] * i % mod;
		inv_fact.back() = pow(fact.back(), mod - 2, mod);
		for (int i = n - 2; i >= 2; i--)
			inv_fact[i] = inv_fact[i + 1] * (i + 1LL) % mod;
	}
	//classic n choose k
	//fails when n >= mod
	int choose(int n, int k) const {
		if (k < 0 || k > n) return 0;
		//now we know 0 <= k <= n so 0 <= n
		return 1LL * fact[n] * inv_fact[k] % mod * inv_fact[n - k] % mod;
	}
	//lucas theorem to calculate n choose k in O(log(k))
	//need to calculate all factorials in range [0,mod), so O(mod) time&space, so need smallish prime mod (< 1e6 maybe)
	//handles n >= mod correctly
	int choose_with_lucas_theorem(long long n, long long k) const {
		if (k < 0 || k > n) return 0;
		if (k == 0 || k == n) return 1;
		return 1LL * choose_with_lucas_theorem(n / mod, k / mod) * choose(n % mod, k % mod) % mod;
	}
	//returns x such that x * n % mod == 1
	int inv(int n) const {
		assert(1 <= n); //don't divide by 0 :)
		return 1LL * fact[n - 1] * inv_fact[n] % mod;
	}
	int mod;
	vector<int> fact, inv_fact;
};
