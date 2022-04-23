#include "../test_utilities/template.h"
#include "../test_utilities/random.h"

#include "../../content/math/exp_mod.h"

void doTest(int base, int power, int mod) {

	int fast = fastPow(base, power, mod);

	int slow = 1;
	for(int i = 0; i < power; i++) {
		slow = (1LL * slow * base) % mod;
	}

	assert(fast == slow);
}

int main() {
	for(int base = 0; base < 16; base++) {
		for(int power = 0; power < 16; power++) {
			for(int mod = 1; mod < 16; mod++) {
				doTest(base, power, mod);
			}
		}
	}
	for(int tests = 1000; tests--;) {
		int base = getRand(0, 1e9+100);
		int power = getRand(0, 100);
		int mod = getRand(1, 1e9+100);

		doTest(base, power, mod);
	}

	cout << "Tests passed!" << endl;
	return 0;
}
