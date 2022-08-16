#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_4_A"
#include "../../template.h"
#include "../../random.h"

#include "../../../library/range_data_structures/uncommon/implicit_seg_tree.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	struct vertical_edge {
		int x, y1, y2, add;
	};
	vector<vertical_edge> edges;
	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		edges.push_back({x1, y1, y2, 1});
		edges.push_back({x2, y1, y2, -1});
	}
	sort(edges.begin(), edges.end(), [&](const vertical_edge & a, const vertical_edge & b) -> bool {
		return a.x < b.x;
	});
	const int mn = -1e9, mx = 1e9;
	implicit_seg_tree < 2000 * 31 * 2 * 2 + 100 > ist(mn, mx);
	long long area = 0;
	//sweepline
	for (int i = 0; i < (int)edges.size();) {
		if (i) {
			auto [curr_mn, cnt_mn] = ist.query(mn, mx);
			int num_pos = mx - mn;
			if (curr_mn == 0) num_pos -= cnt_mn;
			area += 1LL * (edges[i].x - edges[i - 1].x) * num_pos;
		}
		int j = i;
		while (j < (int)edges.size() && edges[i].x == edges[j].x) {
			ist.update(edges[j].y1, edges[j].y2, edges[j].add);
			j++;
		}
		i = j;
	}
	cout << area << '\n';
	return 0;
}
