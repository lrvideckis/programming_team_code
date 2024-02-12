#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3277"
#include "../template.hpp"

#include "../../../library/math/matrix_related/xor_basis.hpp"

//https://github.com/suisen-cp/cp-library-cpp/blob/main/library/linear_algebra/xor_base.hpp
template <class T> basis<T> intersection(const basis<T>& a, const basis<T>& b) {
	vector<array<T, 2>> c;
	transform(begin(a.b), end(a.b), back_inserter(c), [](T e) -> array<T, 2> {
		return {e, e};
	});
	basis<T> res;
	for (T e : b.b) {
		T s = 0;
		for (auto [v, t] : c) {
			T w = e ^ v;
			if (w < e) e = w, s ^= t;
		}
		if (e) c.push_back({e, s});
		else assert(res.add(s));
	}
	return res;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int k;
	cin >> k;
	vector<vector<long long>> grid(k);
	for (int i = 0; i < k; i++) {
		int siz;
		cin >> siz;
		grid[i].resize(siz);
	}
	for (auto& row : grid)
		for (auto& elem : row)
			cin >> elem;
	vector<basis<long long>> basises(1 << k);
	for (int i = 0; i < k; i++) {
		basis<long long> curr;
		int naive_size = 0;
		for (auto elem : grid[i]) {
			long long val1 = curr.shrink(elem);
			long long val2 = curr.shrink(val1);
			assert(val1 == val2);
			for (long long v : curr.b)
				assert(((1LL << __lg(v)) & val2) == 0);
			naive_size += curr.add(elem);
			assert(naive_size == ssize(curr.b));
		}
		for (int i1 = 0; i1 < ssize(curr.b); i1++) {
			for (int i2 = i1 + 1; i2 < ssize(curr.b); i2++) {
				assert(__lg(curr.b[i1]) != __lg(curr.b[i2]));
				assert(((1LL << __lg(curr.b[i1])) & curr.b[i2]) == 0);
			}
		}
		basises[1 << i] = curr;
	}
	long long res = 0;
	for (int mask = 1; mask < (1 << k); mask++) {
		if (__builtin_popcount(mask) > 1) {
			basis u = basises[mask & -mask];
			basis v = basises[mask & (mask - 1)];
			basises[mask] = intersection(u, v);
			basis u_v_union = u;
			for (long long vec : v.b) u_v_union.add(vec);
			assert(ssize(basises[mask].b) + ssize(u_v_union.b) == ssize(u.b) + ssize(v.b));
			basis v_u_union = v;
			for (long long vec : u.b) v_u_union.add(vec);
			assert(ssize(u_v_union.b) == ssize(v_u_union.b));
			for (long long vec : basises[mask].b) {
				long long curr = u.shrink(vec);
				assert(curr == 0);
				curr = v.shrink(vec);
				assert(curr == 0);
			}
		}
		if (__builtin_popcount(mask) % 2 == 1) res += 1LL << ssize(basises[mask].b);
		else res -= 1LL << ssize(basises[mask].b);
	}
	cout << res << '\n';
	return 0;
}
