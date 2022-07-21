#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "../../template.h"

#include "../../../library/range_data_structures/range_hook.h"

int main() {
	for(int n = 0; n <= 100; n++) {
		range_hook rh(n);
		//initialize range bounds
		vector<int> left(2 * n), right(2 * n);
		for(int i = 0; i < n; i++) {
			left[rh.leaf_idx(i)] = i;
			right[rh.leaf_idx(i)] = i + 1;
		}
		for(int i = n - 1; i >= 1; i--) {
			left[i] = left[2 * i];
			right[i] = right[2 * i + 1];
		}

		for(int i = 0; i < n; i++) {
			assert(rh.arr_idx(rh.leaf_idx(i)) == i);
			assert(n <= rh.leaf_idx(i) && rh.leaf_idx(i) < 2 * n);
			assert(0 <= rh.arr_idx(i + n) && rh.arr_idx(i + n) < n);
		}

		for(int l = 0; l <= n; l++) {
			rh.for_each(l, l, [&](int v) -> void {
				assert(false);
			});
			rh.for_parents_up(l, l, [&](int v) -> void {
				assert(false);
			});
			rh.for_each_l_to_r(l, l, [&](int v) -> void {
				assert(false);
			});
			rh.for_parents_down(l, l, [&](int v) -> void {
				assert(false);
			});
			for(int r = l; r <= n; r++) {
				set<int> range_nodes, naive_pars;
				rh.for_each(l, r, [&](int v) -> void {
					assert(1 <= v && v < 2 * n);
					assert(!range_nodes.count(v));//assert uniqueness
					range_nodes.insert(v);
					for(int curr_parent = (v >> 1); curr_parent >= 1; curr_parent >>= 1)
						naive_pars.insert(curr_parent);
				});
				if(r - l == 1) assert((int)range_nodes.size() == 1 && rh.leaf_idx(l) == *range_nodes.begin());
				{
					int cnt = 0;
					int prev_l = l;
					rh.for_each_l_to_r(l, r, [&](int v) -> void {
						assert(1 <= v && v < 2 * n);
						assert(prev_l == left[v]);
						prev_l = right[v];
						assert(range_nodes.count(v));
						cnt++;
					});
					assert(prev_l == r);
					assert(cnt == (int)range_nodes.size());
				}

				set<int> pars;
				rh.for_parents_down(l, r, [&](int v) -> void {
					assert(1 <= v && v < n);
					assert(!pars.count(v));
					pars.insert(v);
				});

				{
					int cnt = 0;
					rh.for_parents_up(l, r, [&](int v) -> void {
						assert(1 <= v && v < n);
						assert(pars.count(v));
						cnt++;
					});
					assert(cnt == (int)pars.size());
				}

				assert(pars == naive_pars);
			}
		}
	}

	int a, b;
	cin >> a >> b;
	cout << a + b << endl;
	return 0;
}
