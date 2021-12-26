#include "../test_utilities/template.h"
#include "../test_utilities/random.h"

#include "../../content/math/n_choose_k_mod.h"

int main() {
	for(int tests = 10; tests--;) {
		int mod;
		while(true) {
			mod = getRand(2, 1e9+100);
			bool isPrime = true;
			for(int i = 2; i * i <= mod; i++) {
				if(mod%i == 0) {
					isPrime = false;
					break;
				}
			}
			if(isPrime) break;
		}

		cout << "mod: " << mod << endl;

		int n = 1000;
		vector<vector<int>> choose(n+1, vector<int>(n+1, 0));

		NchooseK nk(n+1, mod);

		for(int i = 0; i <= n; i++) {
			assert(nk.choose(i, -1) == 0);
			assert(nk.choose(i, i+1) == 0);

			choose[i][0] = 1;

			for(int j = 1; j <= i; j++) {
				choose[i][j] = (choose[i-1][j] + choose[i-1][j-1]) % mod;
			}

			for(int j = 0; j <= i; j++) {
				assert(nk.choose(i, j) == choose[i][j]);
			}
		}

		//doTest(base, power, mod);
	}

	cout << "Tests passed!" << endl;
	return 0;
}
