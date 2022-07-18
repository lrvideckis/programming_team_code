#include "../../template.h"
#include "../../random.h"

#include "../../../library/range_data_structures/uncommon/implicit_seg_tree.h"



int main() {
	const int mx = 1000;

	for(int tests = 50; tests--;) {
		int l = getRand(-mx, mx);
		int r = getRand(-mx, mx);
		if(l > r) swap(l,r);
		if(l == r) r++;

		implicit_seg_tree ist(l, r);

		map<int, long long> naive;

		for(int iterations = 1000; iterations--;) {
			int L = getRand(l, r - 1), R = getRand(l, r - 1);
			if(L > R) swap(L, R);
			if(getRand(1,2) == 1) {//update
				int diff = getRand<int>(-1e9, 1e9);
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
	cout << "Tests passed!" << endl;
	return 0;
}
