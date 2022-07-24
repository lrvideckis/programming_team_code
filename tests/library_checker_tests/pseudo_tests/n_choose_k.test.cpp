#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "../../template.h"
#include "../../random.h"

#include "../../../library/math/n_choose_k_mod.h"

int main() {
	for(int tests = 10; tests--;) {
		int mod;
		{
			int type = get_rand(1, 2);
			while(true) {
				if(type == 1) mod = get_rand(2, (int)1e9+100);
				else mod = get_rand(2, 1000);
				bool isPrime = true;
				for(int i = 2; i * i <= mod; i++) {
					if(mod%i == 0) {
						isPrime = false;
						break;
					}
				}
				if(isPrime) break;
			}
		}

		cerr << "mod: " << mod << endl;

		int n = 1000;
		vector<vector<int>> choose(n+1, vector<int>(n+1, 0));
		for(int i = 0; i <= n; i++) {
			choose[i][0] = 1;
			for(int j = 1; j <= i; j++) {
				choose[i][j] = (choose[i-1][j] + choose[i-1][j-1]) % mod;
			}
		}

		n_choose_k nk(min(n+1,mod), mod);

		{
			vector<int> inv(n + 1);
			inv[1] = 1;
			for (int i = 2; i <= n; i ++) inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
			for(int i = 1; i < min(n+1,mod); i++) {
				assert(nk.inv(i) == inv[i]);
				assert(1LL * nk.inv(i) * i % mod == 1);
			}
		}

		for(int i = 0; i <= n; i++) {
			assert(nk.choose(i, -1) == 0);
			assert(nk.choose(i, i+1) == 0);
			assert(nk.choose_with_lucas_theorem(i, -1) == 0);
			assert(nk.choose_with_lucas_theorem(i, i+1) == 0);
			for(int j = 0; j <= i; j++) {
				assert(nk.choose_with_lucas_theorem(i, j) == choose[i][j]);
				if(i < mod)
					assert(nk.choose(i, j) == choose[i][j]);
			}
		}
	}

	int a, b;
	cin >> a >> b;
	cout << a + b << endl;
	return 0;
}
