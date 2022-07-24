#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "../../template.h"
#include "../../random.h"

#include "../../../library/range_data_structures/uncommon/implicit_seg_tree.h"

int main() {
	const int mx = 1000;

	for(int tests = 50; tests--;) {
		int l = get_rand(-mx, mx);
		int r = get_rand(-mx, mx);
		if(l > r) swap(l,r);
		if(l == r) r++;

		implicit_seg_tree<10'000'000> ist(l, r);

		map<int, long long> naive;

		for(int iterations = 1000; iterations--;) {
			int L = get_rand(l, r - 1), R = get_rand(l, r - 1);
			if(L > R) swap(L, R);
			if(get_rand(1,2) == 1) {//update
				int diff = get_rand<int>(-1e9, 1e9);
				ist.update(L, R, diff);
				for(int i = L; i < R; i++) naive[i] += diff;
			} else {//query
				array<long long, 3> curr_naive = {0, -(long long)1e18, (long long)1e18};
				for(int i = L; i < R; i++) {
					curr_naive[0] += naive[i];
					curr_naive[1] = max(curr_naive[1], naive[i]);
					curr_naive[2] = min(curr_naive[2], naive[i]);
				}
				assert(curr_naive == ist.query(L,R));
			}
		}
	}
	int a, b;
	cin >> a >> b;
	cout << a + b << endl;
	return 0;
}
