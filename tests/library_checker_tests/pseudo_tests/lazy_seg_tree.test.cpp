#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "../../template.h"
#include "../../random.h"

#include "../../../library/range_data_structures/seg_tree.h"

void do_test(int n, int q) {
	const int mx_val = 1e9;

	vector<long long> arr(n);
	for(int i = 0; i < n; i++)
		arr[i] = getRand(-mx_val, mx_val);

	seg_tree st(arr);

	for(int iterations = q; iterations--;) {
		int L = getRand(0,n), R = getRand(0,n);
		if(L > R) swap(L,R);
		if(getRand(1,2) == 1) {//update
			long long diff = getRand(-mx_val, mx_val);
			st.update(L, R, diff);
			for(int i = L; i < R; i++) arr[i] += diff;
		} else {//query
			seg_tree::dt mn = 1e18;
			for(int i = L; i < R; i++) {
				mn = min(mn, arr[i]);
			}
			assert(mn == st.query(L, R));
		}
	}
}

int main() {
	for(int n = 0; n <= 16; n++) {
		do_test(n, n * n);
	}
	for(int tests = 50; tests--;) {
		do_test(getRand(1, 1000), 5000);
	}
	int a, b;
	cin >> a >> b;
	cout << a + b << endl;
	return 0;
}
