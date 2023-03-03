#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_G"
#include "../template.hpp"

#include "../../../library/range_data_structures/lazy_segment_tree.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	{
		//test empty seg tree
		seg_tree st(vector<long long>(0));
		st.update(0, 0, 1);
		long long res = st.query(0, 0);
		assert(res == 0);
		/*
		st.update_iter(0, 0, 1);
		res = st.query_iter(0, 0);
		assert(res == 0);
		*/
	}
	int n, q;
	cin >> n >> q;
	seg_tree st(n);
	while (q--) {
		int type, l, r;
		cin >> type >> l >> r;
		l--;
		if (type == 0) {
			long long x;
			cin >> x;
			//if (q % 2)
			//st.update_iter(l, r, x);
			//else
			st.update(l, r, x);
			//st.update_iter(l, l, 1);
			//st.update_iter(r, r, 1);
			st.update(l, l, 1);
			st.update(r, r, 1);
		} else {
			assert(type == 1);
			//if (q % 2)
			//cout << st.query_iter(l, r) << '\n';
			//else
			cout << st.query(l, r) << '\n';
			/*
			{
			long long res = st.query_iter(l, l);
			assert(res == 0);
			}
			{
			long long res = st.query_iter(r, r);
			assert(res == 0);
			}
			*/
			{
				long long res = st.query(l, l);
				assert(res == 0);
			}
			{
				long long res = st.query(r, r);
				assert(res == 0);
			}
		}
	}
	return 0;
}
