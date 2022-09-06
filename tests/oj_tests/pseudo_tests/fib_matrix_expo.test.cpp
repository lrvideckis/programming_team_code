#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "../../../kactl/stress-tests/utilities/template.h"
#include "../../random.h"

#include "../../../kactl/content/data-structures/Matrix.h"
#include "../../../ac-library/atcoder/modint.hpp"
#include "../../../library/math/fib.h"

void check(long long n) {
	const int MOD = 1e9 + 7;
	Matrix<atcoder::static_modint<MOD>, 2> A;
	A.d = {{{{1,1}}, {{1,0}}}};
	vector<atcoder::static_modint<MOD>> vec = {1,0};
	assert(fib(n, MOD) == ((A^n) * vec)[0]);
}

int main() {
	for (int i = 0; i < 500; i++)
		check(i);
	for (int tests = 1000; tests--;) {
		auto pw = get_rand<long long>(0, 1e18);
		check(pw);
	}
	int a, b;
	cin >> a >> b;
	cout << a + b << endl;
	return 0;
}
