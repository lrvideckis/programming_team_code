#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/misc/random.hpp"

#include "../../../library/range_data_structures/uncommon/distinct_query.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	for (int tests = 5; tests--;) {
		int n = get_rand(1, 100);
		vector<int> arr(n);
		if (get_rand(0, 2) == 1) {
			for (int i = 0; i < n; i++)
				arr[i] = get_rand<int>(-1e9, 1e9);
		} else {
			for (int i = 0; i < n; i++)
				arr[i] = get_rand<int>(-2, 3);
		}
		distinct_query pst(arr);
		for (int l = 0; l < n; l++) {
			for (int r = l; r <= n; r++) {
				set<int> copy_arr(arr.begin() + l, arr.begin() + r);
				assert(pst.query(l, r) == (int)copy_arr.size());
			}
		}
	}
	cout << "Hello World\n";
	return 0;
}
