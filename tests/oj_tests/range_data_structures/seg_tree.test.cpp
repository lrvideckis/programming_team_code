#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_H"
#include "../../template.h"

#include "../../../library/range_data_structures/seg_tree.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);

	{
		//test empty seg tree
		seg_tree st(vector<long long>(0));
		st.query(0, 0);
		st.update(0, 0, 1);
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
		} else
			cout << st.query(l, r) << '\n';
	}
	return 0;
}
