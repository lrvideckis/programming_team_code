#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_H"
#include "../template.hpp"

#include "../../../library/range_data_structures/lazy_segment_tree.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	{
		//test empty seg tree
		seg_tree st(vector<long long>(0));
		st.update(0, 0, 1);
		long long res = st.query(0, 0);
		assert(res == seg_tree::UNIT);
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
			if (q % 2)
				st.update(l, r, x);
			else
				st.update(1, l, r, x);
			st.update(l, l, 1);
			st.update(r, r, 1);
			st.update(1, l, l, 1);
			st.update(1, r, r, 1);
		} else {
			if (q % 2)
				cout << st.query(l, r) << '\n';
			else
				cout << st.query(1, l, r) << '\n';
			{
				long long res = st.query(l, l);
				assert(res == seg_tree::UNIT);
			}
			{
				long long res = st.query(r, r);
				assert(res == seg_tree::UNIT);
			}
			{
				long long res = st.query(1, l, l);
				assert(res == seg_tree::UNIT);
			}
			{
				long long res = st.query(1, r, r);
				assert(res == seg_tree::UNIT);
			}
		}
	}
	return 0;
}
