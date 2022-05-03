#include "../../template.h"
#include "../test_utilities/generators/random.h"

#include "../../../Library/range_data_structures/implicitLazySegTree.h"



int main() {
	const int mx = 1000;

	for(int tests = 50; tests--;) {
		int l = getRand(-mx, mx);
		int r = getRand(-mx, mx);
		if(l > r) swap(l,r);

		implicitLazySegTree ist(l, r);

		map<int, long long> naive;

		for(int iterations = 1000; iterations--;) {
			int L = getRand(l, r), R = getRand(l, r);
			if(L > R) swap(L,R);
			if(getRand(1,2) == 1) {//update
				int diff = getRand(-1e9, 1e9);
				ist.update(L, R, diff);
				for(int i = L; i <= R; i++) naive[i] += diff;
			} else {//query
				long long sum = naive[L];
				for(int i = L+1; i <= R; i++) {
					sum += naive[i];
				}
				assert(sum == ist.query(L,R));
			}
		}
	}
	cout << "Tests passed!" << endl;
	return 0;
}
