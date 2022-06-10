#include "../../template.h"
#include "../../random.h"

#include "../../../library/math/matrix_expo.h"
#include "../../../library/math/fib.h"

void check(long long n) {
	const int mod = 1e9 + 7;
	assert(fib(n, mod) == mult(power({{1, 1}, {1, 0}}, n, mod), {{1}, {0}}, mod)[0][0]);

}

int main() {
	for(int i = 0; i < 500; i++) {
		check(i);
	}
	for(int tests = 1000; tests--;) {
		long long pw = getRand<long long>(0, 1e18);
		check(pw);
	}
	cout << "Tests passed!" << endl;
	return 0;
}
