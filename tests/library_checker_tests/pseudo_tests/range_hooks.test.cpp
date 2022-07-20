#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "../../template.h"
#include "../../random.h"

#include "../../../library/range_data_structures/range_hook.h"

int main() {
	for(int n = 0; n <= 100; n++) {
		range_hook rh(n);
		for(int i = 0; i < n; i++) {
			assert(rh.arr_idx(rh.leaf_idx(i)) == i);
			assert(n <= rh.leaf_idx(i) && rh.leaf_idx(i) < 2 * n);
			assert(0 <= rh.arr_idx(i + n) && rh.arr_idx(i + n) < n);
		}

		for(int l = 0; l <= n; l++) {
			for(int r = l; r <= n; r++) {
				{//range operations
					vector<int> range_idxs;
					rh.for_each(l, r, [&](int v) -> void {
							assert(1 <= v && v < 2 * n);
							range_idxs.push_back(v);
							});
					{
						vector<int> check_uniq(range_idxs);
						sort(check_uniq.begin(), check_uniq.end());
						check_uniq.erase(unique(check_uniq.begin(), check_uniq.end()), check_uniq.end());
						assert(check_uniq.size() == range_idxs.size());
					}
					vector<int> range_idxs_l_to_r;
					rh.for_each_l_to_r(l, r, [&](int v) -> void {
							assert(1 <= v && v < 2 * n);
							range_idxs_l_to_r.push_back(v);
							});
					{
						vector<int> check_uniq(range_idxs_l_to_r);
						sort(check_uniq.begin(), check_uniq.end());
						check_uniq.erase(unique(check_uniq.begin(), check_uniq.end()), check_uniq.end());
						assert(check_uniq.size() == range_idxs_l_to_r.size());
					}
					sort(range_idxs.begin(), range_idxs.end());
					sort(range_idxs_l_to_r.begin(), range_idxs_l_to_r.end());
					assert(range_idxs == range_idxs_l_to_r);
				}
				{//for each parent
					vector<int> par_down;
					rh.for_parents_down(l, r, [&](int v) -> void {
						assert(1 <= v && v < n);
						par_down.push_back(v);
					});
					{
						int prev_sz = par_down.size();
						sort(par_down.begin(), par_down.end());
						par_down.erase(unique(par_down.begin(), par_down.end()), par_down.end());
						assert(prev_sz == (int)par_down.size());
					}
					vector<int> par_up;
					rh.for_parents_down(l, r, [&](int v) -> void {
						assert(1 <= v && v < n);
						par_up.push_back(v);
					});
					{
						int prev_sz = par_up.size();
						sort(par_up.begin(), par_up.end());
						par_up.erase(unique(par_up.begin(), par_up.end()), par_up.end());
						assert(prev_sz == (int)par_up.size());
					}
					assert(par_down == par_up);

					set<int> all_ancs;
					for(int v = rh.range_idx(l); v; v /= 2) all_ancs.insert(v);
					for(int v = rh.range_idx(r); v; v /= 2) all_ancs.insert(v);
					for(int v : par_up) {
						assert(all_ancs.count(v));
					}
				}
			}
		}
	}

	int a, b;
	cin >> a >> b;
	cout << a + b << endl;
	return 0;
}
