#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "../../template.h"
#include "../../random.h"

#include "../../../library/range_data_structures/uncommon/implicit_seg_tree.h"

int main() {
	const int MX = 1000;

	for(int tests = 50; tests--;) {
		int range_l = get_rand(-MX, MX);
		int range_r = get_rand(-MX, MX);
		if(range_l > range_r) swap(range_l,range_r);
		if(range_l == range_r) range_r++;

		implicit_seg_tree<10'000'000> ist(range_l, range_r);

		map<int, long long> naive;

		for(int iterations = 1000; iterations--;) {
			int l = get_rand(range_l, range_r - 1), r = get_rand(range_l, range_r - 1);
			if(l > r) swap(l, r);
			if(get_rand(1,2) == 1) {//update
				int diff = get_rand<int>(-1e9, 1e9);
				ist.update(l, r, diff);
				for(int i = l; i < r; i++) naive[i] += diff;
			} else {//query
				array<long long, 3> curr_naive = {0, -(long long)1e18, (long long)1e18};
				for(int i = l; i < r; i++) {
					curr_naive[0] += naive[i];
					curr_naive[1] = max(curr_naive[1], naive[i]);
					curr_naive[2] = min(curr_naive[2], naive[i]);
				}
				assert(curr_naive == ist.query(l,r));
			}
		}
	}
	int a, b;
	cin >> a >> b;
	cout << a + b << endl;
	return 0;
}
