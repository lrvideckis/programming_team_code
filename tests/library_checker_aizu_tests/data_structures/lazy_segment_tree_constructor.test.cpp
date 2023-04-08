#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../template.hpp"

#include "../../../library/data_structures/uncommon_data_structures/iterative_lazy_segment_tree.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	{
		//test empty seg tree
		iter_seg_tree ist(vector<long long>(0));
		ist.update_iter(0, 0, 1);
		long long res = ist.query_iter(0, 0);
		assert(res == 0);
		ist.st.update(0, 0, 1);
		res = ist.st.query(0, 0);
		assert(res == 0);
	}
	int n, q;
	cin >> n >> q;
	vector<long long> arr(n);
	for (int i = 0; i < n; i++) cin >> arr[i];
	iter_seg_tree ist(arr);
	{
		int pw2 = 1;
		while (pw2 < n) pw2 *= 2;
		assert(arr[0] == ist.st.tree[pw2]);
	}
	while (q--) {
		int type;
		cin >> type;
		if (type == 0) {
			int idx;
			long long x;
			cin >> idx >> x;
			if (q % 2)
				ist.update_iter(idx, idx + 1, x);
			else
				ist.st.update(idx, idx + 1, x);
			ist.update_iter(idx, idx, 1);
			ist.st.update(idx, idx, 1);
		} else {
			assert(type == 1);
			int l, r;
			cin >> l >> r;
			if (q % 2)
				cout << ist.query_iter(l, r) << '\n';
			else
				cout << ist.st.query(l, r) << '\n';
			{
				long long res = ist.query_iter(l, l);
				assert(res == 0);
			}
			{
				long long res = ist.query_iter(r, r);
				assert(res == 0);
			}
			{
				long long res = ist.st.query(l, l);
				assert(res == 0);
			}
			{
				long long res = ist.st.query(r, r);
				assert(res == 0);
			}
		}
	}
	return 0;
}
