#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../template.hpp"

#include "../../../library/range_data_structures/lazy_segment_tree.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	vector<long long> arr(n);
	for(int i = 0; i < n; i++) cin >> arr[i];
	seg_tree st(arr);
	while (q--) {
		int type;
		cin >> type;
		if (type == 0) {
			int idx;
			long long x;
			cin >> idx >> x;
			//if (q % 2)
				//st.update_iter(l, r, x);
			//else
				st.update(idx, idx + 1, x);
			//st.update_iter(l, l, 1);
			//st.update_iter(r, r, 1);
			st.update(idx, idx, 1);
		} else {
			assert(type == 1);
			int l, r;
			cin >> l >> r;
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
