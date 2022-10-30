#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../kactl_macros.hpp"
#include "../../../library/misc/random.hpp"

#include "../../../kactl/content/data-structures/Matrix.h"
#include "../../../library/math/fibonacci.hpp"
#include "../../../library/range_data_structures/uncommon/disjoint_rmq.hpp"

const int MOD = 1'000'000'007;

#include "../../../hackpack-cpp/content/number-theory/ModInt.h"

void check(ll n, bool is_small) {
	using mat_2_by_2 = Matrix<mi, 2>;
	mat_2_by_2 mat;
	mat.d = {{{{1, 1}}, {{1, 0}}}};
	vector<mi> vec = {1, 0};
	ll res = fib(n, MOD);
	assert(res == int(((mat ^ n) * vec)[0]));
	if (is_small && n > 0) {
		mat_2_by_2 identity;
		identity.d = {{{{1, 0}}, {{0, 1}}}};
		disjoint_rmq<mat_2_by_2> rmq(vector<mat_2_by_2>(n + 5, mat), identity, [](const auto & x, const auto & y) {
			return x * y;
		});
		for (int le = 0, ri = int(n); ri <= int(n) + 5; le++, ri++)
			assert(res == int((rmq.query(le, ri) * vec)[0]));
	}
}

int main() {
	for (int i = 0; i < 500; i++)
		check(i, 1);
	for (int tests = 1000; tests--;)
		check(get_rand<long long>(0, 1e18), 0);
	cout << "Hello World\n";
	return 0;
}
