#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/misc/random.hpp"
#include "../../../library/math/fibonacci.hpp"

const int MOD = 1'000'000'007;
#include "../kactl_macros.hpp"
#include "../../../kactl/content/data-structures/Matrix.h"
#include "../../../hackpack-cpp/content/number-theory/ModInt.h"

void check(long long n) {
	using mat_2_by_2 = Matrix<mi, 2>;
	mat_2_by_2 mat;
	mat.d = {{{{1, 1}}, {{1, 0}}}};
	vector<mi> vec = {1, 0};
	long long res = fib(n, MOD);
	assert(res == int(((mat ^ n) * vec)[0]));
}

int main() {
	for (int i = 0; i < 500; i++)
		check(i);
	for (int tests = 1000; tests--;)
		check(get_rand<long long>(0, 1e18));
	cout << "Hello World\n";
	return 0;
}
