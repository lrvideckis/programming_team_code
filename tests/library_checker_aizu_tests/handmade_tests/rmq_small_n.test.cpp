#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/misc/random.hpp"

#include "../../../library/data_structures/sparse_table.hpp"
#include "../../../library/data_structures/uncommon_data_structures/disjoint_sparse_table.hpp"
#include "../../../library/data_structures/uncommon_data_structures/linear_rmq.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	for (int n = 1; n <= 100; n++) {
		for (int times = 0; times < 40; times++) {
			vector<int> arr(n);
			for (int i = 0; i < n; i++) arr[i] = get_rand<int>(INT_MIN, INT_MAX);
			RMQ<int> rmq(arr, [](auto x, auto y) {return min(x, y);});
			disjoint_rmq<int> dis_rmq(arr, [](auto x, auto y) {return min(x, y);});
			linear_rmq<int> lin_rmq(arr, less());
			for (int le = 0; le < n; le++) {
				for (int ri = le + 1; ri <= n; ri++) {
					int idx_min = lin_rmq.query_idx(le, ri);
					assert(le <= idx_min && idx_min < ri);
					assert(arr[idx_min] == rmq.query(le, ri));
					assert(arr[idx_min] == dis_rmq.query(le, ri));
				}
			}
		}
	}
	cout << "Hello World\n";
}
