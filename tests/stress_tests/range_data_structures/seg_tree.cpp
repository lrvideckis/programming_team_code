#include "../../template.h"
#include "../../random.h"

#include "../../../library/range_data_structures/seg_tree.h"

const int mx_val = 1e9;

tuple<seg_tree, vector<long long>> treeFactory(int n) {
	if(getRand(1, 2) == 1) {
		vector<long long> arr(n);
		for(int i = 0; i < n; i++) {
			arr[i] = getRand(-mx_val, mx_val);
		}
		return make_tuple(seg_tree(arr), arr);
	}
	return make_tuple(seg_tree(vector<long long>(n, 0)), vector<long long>(n, 0));
}

int main() {
	for(int tests = 50; tests--;) {
		int n = getRand(1, 1000);
		auto [st, arr] = treeFactory(n);

		for(int iterations = 5000; iterations--;) {
			int L = getRand(0,n), R = getRand(0,n);
			if(L > R) swap(L,R);
			if(getRand(1,2) == 1) {//update
				long long diff = getRand(-mx_val, mx_val);
				st.update(L, R, diff);
				for(int i = L; i < R; i++) arr[i] += diff;
			} else {//query
				long long sum = 0, mx = -1e18, mn = 1e18;
				for(int i = L; i < R; i++) {
					mn = min(mn, arr[i]);
					mx = max(mx, arr[i]);
					sum += arr[i];
				}
				seg_tree::dt res = st.query(L, R);
				assert(res[0] == sum);
				assert(res[1] == mx);
				assert(res[2] == mn);
			}
		}
	}
	cout << "Tests passed!" << endl;
	return 0;
}
