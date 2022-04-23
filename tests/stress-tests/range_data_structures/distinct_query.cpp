#include "../test_utilities/template.h"
#include "../test_utilities/generators/random.h"

#include "../../../Library/range_data_structures/distinct_query.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);
	for(int tests = 5; tests--;) {
		int n = getRand(1, 100);
		vector<int> arr(n);
		for(int i = 0; i < n; i++) {
			arr[i] = getRand(0, 1e9);
		}
		persistentSegTree pst(arr);
		for(int l = 0; l < n; l++) {
			for(int r = l; r < n; r++) {
				set<int> copyArr(arr.begin() + l, arr.begin() + r + 1);
				assert(pst.query(l, r) == (int)copyArr.size());
			}
		}
	}
	return 0;
}
