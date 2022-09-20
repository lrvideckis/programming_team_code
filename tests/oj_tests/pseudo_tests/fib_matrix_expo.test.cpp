#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../../template.hpp"
#include "../../kactl_macros.hpp"
#include "../../../library/misc/random.hpp"

#include "../../../kactl/content/data-structures/Matrix.h"
#include "../../../ac-library/atcoder/modint.hpp"
#include "../../../library/math/fibonacci.hpp"

void check(long long n) {
	const int MOD = 1e9 + 7;
	Matrix<atcoder::static_modint<MOD>, 2> mat;
	mat.d = {{{{1, 1}}, {{1, 0}}}};
	vector<atcoder::static_modint<MOD>> vec = {1, 0};
	assert(fib(n, MOD) == ((mat ^ n) * vec)[0]);
}

int main() {
	for (int i = 0; i < 500; i++)
		check(i);
	for (int tests = 1000; tests--;) {
		auto pw = get_rand<long long>(0, 1e18);
		check(pw);
	}
	cout << "Hello World\n";
	return 0;
}
