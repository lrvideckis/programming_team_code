#include "../test_utilities/template.h"
#include "../test_utilities/random.h"

#include "../../content/range_data_structures/segTree.h"
#include "../../content/range_data_structures/implicitLazySegTree.h"

const int mx = 1e9;

tuple<SegmentTree, implicitLazySegTree, vector<ll>> treeFactory(int n) {
	if(getRand(1, 2) == 1) {
		vector<ll> arr(n);
		for(int i = 0; i < n; i++) {
			arr[i] = getRand(-mx, mx);
		}
		return make_tuple(SegmentTree(arr), implicitLazySegTree(arr), arr);
	}
	return make_tuple(SegmentTree(vector<ll>(n, 0)), implicitLazySegTree(0, n-1), vector<ll>(n, 0));
}

int main() {
	for(int tests = 50; tests--;) {
		int n = getRand(1, 1000);
		auto [st, ist, arr] = treeFactory(n);

		for(int iterations = 5000; iterations--;) {
			int L = getRand(0,n-1), R = getRand(0,n-1);
			if(L > R) swap(L,R);
			if(getRand(1,2) == 1) {//update
				ll diff = getRand(-mx, mx);
				st.update(L, R, diff);
				ist.update(L, R, diff);
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

				assert(mx == ist.query(L,R));
			}
		}
	}
	cout << "Tests passed!" << endl;
	return 0;
}
