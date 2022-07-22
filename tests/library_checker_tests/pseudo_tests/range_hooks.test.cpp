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
			assert(n <= rh.leaf_idx(i) && rh.leaf_idx(i) < 2 * n);
		}

		for(int l = 0; l <= n; l++) {
			rh.for_each(l, l, [&](int v) -> void {
				assert(false);
			});
			rh.for_parents_up(l, l, [&](int v) -> void {
				assert(false);
			});
			rh.for_parents_down(l, l, [&](int v) -> void {
				assert(false);
			});
			for(int r = l; r <= n; r++) {
				set<int> naive_pars;
				{
					vector<pair<int,int>> ranges;
					set<int> range_nodes;
					rh.for_each(l, r, [&](int v) -> void {
						assert(1 <= v && v < 2 * n);
						assert(!range_nodes.count(v));//assert uniqueness
						range_nodes.insert(v);
						ranges.emplace_back(left[v], right[v]);
						for(int curr_parent = (v >> 1); curr_parent >= 1; curr_parent >>= 1) naive_pars.insert(curr_parent);
					});
					if(r - l == 1) assert((int)range_nodes.size() == 1 && rh.leaf_idx(l) == *range_nodes.begin());
					if(r - l > 0) {
						sort(ranges.begin(), ranges.end());
						assert(ranges[0].first == l);
						assert(ranges.back().second == r);
						for(int i = 1; i < (int)ranges.size(); i++) {
							assert(ranges[i-1].second == ranges[i].first);
						}
					}
				}

				set<int> pars_down;
				rh.for_parents_down(l, r, [&](int v) -> void {
					assert(1 <= v && v < n);
					pars_down.insert(v);
				});

				set<int> pars_up;
				rh.for_parents_up(l, r, [&](int v) -> void {
					assert(1 <= v && v < n);
					pars_up.insert(v);
				});
				assert(pars_down == pars_up);
				assert(pars_up == naive_pars);
			}
		}
	}

	int a, b;
	cin >> a >> b;
	cout << a + b << endl;
	return 0;
}
