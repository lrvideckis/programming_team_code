#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"
#include "../../template.h"

#include "../../../library/range_data_structures/BIT.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n, q;
	string s;
	cin >> n >> q >> s;

	vector<int> init(n);
	for(int i = 0; i < n; i++)
		init[i] = s[i] - '0';

	BIT<int> ft(init);

	while(q--) {
		int type, k;
		cin >> type >> k;
		if(type == 0) {
			if(ft.sum(k,k) == 0) ft.update(k, 1);
		} else if(type == 1) {
			if(ft.sum(k,k) == 1) ft.update(k, -1);
		} else if(type == 2) {
			cout << ft.sum(k,k) << endl;
		} else if(type == 3) {
			if(ft.sum(k,k) == 1) {
				cout << k << endl;
				continue;
			}
			int order = ft.sum(k);
			int res = ft.lower_bound(order+1);
			if(res == n) res = -1;
			cout << res << endl;
		} else {
			if(ft.sum(k,k) == 1) {
				cout << k << endl;
				continue;
			}
			int order = ft.sum(k);
			int res = ft.lower_bound(order);
			cout << res << endl;
		}
	}
	return 0;
}
