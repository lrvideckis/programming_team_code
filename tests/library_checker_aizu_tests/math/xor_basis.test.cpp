#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3277"
#include "../template.hpp"

#define basis basis_ordered
#include "../../../library/math/matrix_related/xor_basis_ordered.hpp"
#undef basis

#include "../../../library/math/matrix_related/xor_basis_unordered.hpp"

//https://github.com/suisen-cp/cp-library-cpp/blob/main/library/linear_algebra/xor_base.hpp
template <class T> basis<T> intersection(const basis<T>& u, const basis<T>& v) {
	vector<array<T, 2>> c;
	transform(begin(u.b), end(u.b), back_inserter(c), [](T e) -> array<T, 2> {
		return {e, e};
	});
	basis<T> res;
	for (T e : v.b) {
		T s = 0;
		for (auto [x, t] : c) {
			T w = e ^ x;
			if (w < e) e = w, s ^= t;
		}
		if (e) c.push_back({e, s});
		else assert(res.insert(s));
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
		basis<long long> unordered;
		basis_ordered ordered;
		int naive_size = 0;
		for (auto elem : grid[i]) {
			long long val1 = unordered.shrink(elem);
			long long val2 = unordered.shrink(val1);
			assert(val1 == val2);
			for (long long v : unordered.b)
				assert(((1LL << __lg(v)) & val2) == 0);
			bool inserted_unordered = unordered.insert(elem);
			bitset<lg> curr_elem(elem);
			for (int l = 0; l < lg; l++)
				assert(((elem >> l) & 1) == curr_elem[l]);
			bool inserted_ordered = ordered.insert(curr_elem);
			assert(inserted_unordered == inserted_ordered);
			naive_size += inserted_unordered;
			assert(naive_size == ssize(unordered.b));
			assert(ssize(unordered.b) == ordered.siz);
			if (inserted_unordered) {
				for (long long v : unordered.b) {
					curr_elem = bitset<lg>(v);
					int idx = ordered.shrink(curr_elem);
					assert(idx == -1);
				}
				for (int j = 0; j < lg; j++) {
					assert(ordered.b[j][j] == ordered.b[j].any());
					if (ordered.b[j][j]) {
						long long curr_shrink_val = unordered.shrink(ordered.b[j].to_ullong());
						assert(curr_shrink_val == 0);
					}
				}
				for (int i1 = 0; i1 < ssize(unordered.b); i1++) {
					for (int i2 = i1 + 1; i2 < ssize(unordered.b); i2++) {
						assert(__lg(unordered.b[i1]) != __lg(unordered.b[i2]));
						assert(((1LL << __lg(unordered.b[i1])) & unordered.b[i2]) == 0);
					}
				}
			}
		}
		basises[1 << i] = unordered;
	}
	long long res = 0;
	for (int mask = 1; mask < (1 << k); mask++) {
		if (__builtin_popcount(mask) > 1) {
			basis u = basises[mask & -mask];
			basis v = basises[mask & (mask - 1)];
			basises[mask] = intersection(u, v);
			basis u_v_union = u;
			for (long long vec : v.b) u_v_union.insert(vec);
			assert(ssize(basises[mask].b) + ssize(u_v_union.b) == ssize(u.b) + ssize(v.b));
			basis v_u_union = v;
			for (long long vec : u.b) v_u_union.insert(vec);
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
