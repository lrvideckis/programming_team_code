#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_E"
#include "../../template.hpp"

#include "../../../library/math/n_choose_k_mod.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	const int MOD = 1e9 + 7;
	n_choose_k nk(1001, MOD);
	//test mod inverse
	{
		//source: https://codeforces.com/blog/entry/83075
		vector<int> inverse(1001);
		inverse[1] = 1;
		for (int i = 2; i < (int)inverse.size(); i ++)
			inverse[i] = 1LL * (MOD - MOD / i) * inverse[MOD % i] % MOD;
		for (int i = 1; i < (int)inverse.size(); i ++)
			assert(nk.inv(i) == inverse[i]);
	}
	int n, k;
	cin >> n >> k;
	cout << nk.choose(k, n) << '\n';
	return 0;
}
