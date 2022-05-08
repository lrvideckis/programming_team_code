#include "../../template.h"
#include "../../../Library/misc/random.h"

#include "../../../Library/math/n_choose_k_mod.h"

int main() {
	for(int tests = 10; tests--;) {
		int mod;
		{
			int type = getRand(1, 2);
			while(true) {
				if(type == 1) mod = getRand<int>(2, 1e9+100);
				else mod = getRand(2, 1000);
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

		cout << "mod: " << mod << endl;

		int n = 1000;
		vector<vector<int>> choose(n+1, vector<int>(n+1, 0));
		for(int i = 0; i <= n; i++) {
			choose[i][0] = 1;
			for(int j = 1; j <= i; j++) {
				choose[i][j] = (choose[i-1][j] + choose[i-1][j-1]) % mod;
			}
		}

		NchooseK nk(min(n+1,mod), mod);

		for(int i = 1; i < min(n+1,mod); i++) {
			assert(nk.inv(i) == fastPow(i, mod-2, mod));
			assert(1LL * nk.inv(i) * i % mod == 1);
		}

		for(int i = 0; i <= n; i++) {
			assert(nk.choose(i, -1) == 0);
			assert(nk.choose(i, i+1) == 0);
			assert(nk.chooseWithLucasTheorem(i, -1) == 0);
			assert(nk.chooseWithLucasTheorem(i, i+1) == 0);
			for(int j = 0; j <= i; j++) {
				assert(nk.chooseWithLucasTheorem(i, j) == choose[i][j]);
				if(i < mod)
					assert(nk.choose(i, j) == choose[i][j]);
			}
		}
	}

	cout << "Tests passed!" << endl;
	return 0;
}
