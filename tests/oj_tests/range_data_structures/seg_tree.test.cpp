#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_H"
#include "../../template.h"

#include "../../../library/range_data_structures/seg_tree.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	{
		//test empty seg tree
		seg_tree st(vector<long long>(0));
		st.update(0, 0, 1);
		assert(st.query(0, 0) == seg_tree::INF);
	}
	int n, q;
	cin >> n >> q;
	seg_tree st(vector<long long>(n, 0));
	while (q--) {
		int type, l, r;
		cin >> type >> l >> r;
		r++;
		if (type == 0) {
			int x;
			cin >> x;
			st.update(l, r, x);
			st.update(l, l, 1);
			st.update(r, r, 1);
		} else {
			cout << st.query(l, r) << '\n';
			assert(st.query(l, l) == seg_tree::INF);
			assert(st.query(r, r) == seg_tree::INF);
		}
	}
	return 0;
}
