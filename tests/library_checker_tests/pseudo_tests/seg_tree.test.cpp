#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "../../template.h"
#include "../../random.h"

#include "../../../library/range_data_structures/seg_tree.h"

void do_test(int n, int q) {
	const int MX_VAL = 1e9;

	vector<long long> arr(n);
	for(int i = 0; i < n; i++)
		arr[i] = get_rand(-MX_VAL, MX_VAL);

	seg_tree st(arr);

	vector<tuple<int,int,bool>> query;
	if(q == INT_MAX) {
		for(int l = 0; l <= n; l++) {
			for(int r = l; r <= n; r++) {
				query.emplace_back(l, r, 0);
				query.emplace_back(l, r, 1);
			}
		}
	} else {
		for(int i = 0; i < q; i++) {
			int l = get_rand(0, n + 1), r = get_rand(0, n + 1);
			if(l > r) swap(l,r);
			query.emplace_back(l, r, get_rand(0, 2));
		}
	}

	shuffle(query.begin(), query.end(), rng);

	for(auto [l, r, is_update] : query) {
		if(is_update) {//update
			long long diff = get_rand(-MX_VAL, MX_VAL);
			st.update(l, r, diff);
			for(int i = l; i < r; i++) arr[i] += diff;
		} else {//query
			seg_tree::dt mn = seg_tree::INF;
			for(int i = l; i < r; i++) {
				mn = min(mn, arr[i]);
			}
			assert(mn == st.query(l, r));
		}
	}
}

int main() {
	for(int n = 0; n <= 140; n++) {
		do_test(n, INT_MAX);
	}
	for(int tests = 50; tests--;) {
		do_test(get_rand(500, 1000), 5000);
	}
	for(int tests = 8; tests--;) {
		do_test(get_rand((int)1e5, (int)2e5), 50);
	}
	int a, b;
	cin >> a >> b;
	cout << a + b << endl;
	return 0;
}
