#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "../../template.h"
#include "../../random.h"

#include "../../../library/range_data_structures/seg_tree.h"

void do_test(int n, int q) {
	const int mx_val = 1e9;

	vector<long long> arr(n);
	for(int i = 0; i < n; i++)
		arr[i] = get_rand(-mx_val, mx_val);

	seg_tree st(arr);

	for(int iterations = q; iterations--;) {
		int l = get_rand(0,n), r = get_rand(0,n);
		if(l > r) swap(l,r);
		if(get_rand(1,2) == 1) {//update
			long long diff = get_rand(-mx_val, mx_val);
			st.update(l, r, diff);
			for(int i = l; i < r; i++) arr[i] += diff;
		} else {//query
			seg_tree::dt mn = 1e18;
			for(int i = l; i < r; i++) {
				mn = min(mn, arr[i]);
			}
			assert(mn == st.query(l, r));
		}
	}
}

int main() {
	for(int n = 0; n <= 16; n++) {
		do_test(n, n * n);
	}
	for(int tests = 50; tests--;) {
		do_test(get_rand(1, 1000), 5000);
	}
	int a, b;
	cin >> a >> b;
	cout << a + b << endl;
	return 0;
}
