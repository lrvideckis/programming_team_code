#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"
#include "../../template.h"

#include "../../../library/range_data_structures/uncommon/implicit_seg_tree.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n, q;
	cin >> n >> q;

	struct event {
		int x, yl, yr, w, query_id;
		int is_query;
	};
	vector<event> arr;

	for(int i = 0; i < n; i++) {
		int x, y, w;
		cin >> x >> y >> w;
		arr.push_back({x + 1, y, y + 1, w, -1, 0});
	}

	for(int i = 0; i < q; i++) {
		int l, d, r, u;
		cin >> l >> d >> r >> u;
		arr.push_back({l, d, u, -1, i, -1});
		arr.push_back({r, d, u, -1, i, 1});
	}

	sort(arr.begin(), arr.end(), [](const event& u, const event& v) -> bool {
		if(u.x == v.x) {
			if((u.is_query == 0) != (v.is_query == 0)) {
				return u.is_query == 0;
			}
			return false;
		}
		return u.x < v.x;
	});

	implicit_seg_tree ist(0, 1e9 + 10);

	vector<long long> res(q, 0);

	for(auto [x, yl, yr, w, query_id, is_query] : arr) {
		if(is_query) {
			res[query_id] += is_query * ist.query(yl, yr)[0];
		} else {
			ist.update(yl, yr, w);
		}
	}

	for(int i = 0; i < q; i++) {
		cout << res[i] << '\n';
	}
	return 0;
}
