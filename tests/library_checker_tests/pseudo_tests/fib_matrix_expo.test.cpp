#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "../../template.h"
#include "../../random.h"

#include "../../../library/math/matrix_expo.h"
#include "../../../library/math/fib.h"

void check(long long n) {
	const int MOD = 1e9 + 7;
	assert(fib(n, MOD) == mult(power({{1, 1}, {1, 0}}, n, MOD), {{1}, {0}}, MOD)[0][0]);
}

int main() {
	for (int i = 0; i < 500; i++)
		check(i);
	for (int tests = 1000; tests--;) {
		long long pw = get_rand<long long>(0, 1e18);
		check(pw);
	}
	int a, b;
	cin >> a >> b;
	cout << a + b << endl;
	return 0;
}
