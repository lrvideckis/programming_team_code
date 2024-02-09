#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_G"
#include "../template.hpp"

#include "../../../library/data_structures/seg_tree_uncommon/iterative.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	{
		//test empty seg tree
		seg_tree st_empty(0);
		iter_seg_tree lst(st_empty);
		lst.update_iter(0, 0, 1);
		long long res = lst.query_iter(0, 0);
		assert(res == 0);
		lst.st.update(0, 0, 1);
		res = lst.st.query(0, 0);
		assert(res == 0);
	}
	int n, q;
	cin >> n >> q;
	seg_tree st_init(n);
	iter_seg_tree lst(st_init);
	while (q--) {
		int type, l, r;
		cin >> type >> l >> r;
		l--;
		if (type == 0) {
			long long x;
			cin >> x;
			if (q % 2)
				lst.update_iter(l, r, x);
			else
				lst.st.update(l, r, x);
			lst.update_iter(l, l, 1);
			lst.update_iter(r, r, 1);
			lst.st.update(l, l, 1);
			lst.st.update(r, r, 1);
		} else {
			assert(type == 1);
			if (q % 2)
				cout << lst.query_iter(l, r) << '\n';
			else
				cout << lst.st.query(l, r) << '\n';
			{
				long long res = lst.query_iter(l, l);
				assert(res == 0);
			}
			{
				long long res = lst.query_iter(r, r);
				assert(res == 0);
			}
			{
				long long res = lst.st.query(l, l);
				assert(res == 0);
			}
			{
				long long res = lst.st.query(r, r);
				assert(res == 0);
			}
		}
	}
	return 0;
}
