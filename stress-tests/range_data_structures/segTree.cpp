#include "../test_utilities/template.h"
#include "../test_utilities/random.h"

#include "../../content/range_data_structures/segTree.h"

int main() {
	for(int tests = 20; tests--;) {
		int n = getRand(1, 1000);
		vector<ll> arr(n);
		int mx = 1e9;
		for(int i = 0; i < n; i++) {
			arr[i] = getRand(-mx, mx);
		}
		SegmentTree st(arr);
		for(int iterations = 5000; iterations--;) {
			int L = getRand(0,n-1), R = getRand(0,n-1);
			if(L > R) swap(L,R);
			if(getRand(1,2) == 1) {//update
				ll diff = getRand(-mx, mx);
				st.update(L, R, diff);
				for(int i = L; i <= R; i++) arr[i] += diff;
			} else {//query
				ll mn = arr[L], mx = arr[L], sum = arr[L];
				for(int i = L+1; i <= R; i++) {
					mn = min(mn, arr[i]);
					mx = max(mx, arr[i]);
					sum += arr[i];
				}
				SegmentTree::Node res = st.query(L, R);
				assert(res.mn == mn);
				assert(res.mx == mx);
				assert(res.sum == sum);
			}
		}
	}
	cout << "Tests passed!" << endl;
	return 0;
}
