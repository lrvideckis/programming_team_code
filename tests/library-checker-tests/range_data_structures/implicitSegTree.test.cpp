#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../../template.h"

#include "../../stress-tests/test_utilities/random.h"
#include "../../content/range_data_structures/implicitSegTree.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);
	int n,q;
	cin >> n >> q;

	implicitSegTree ist(n);

	vector<int> arr(n);
	vector<int> perm(n);
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
		perm[i] = i;
	}
	for(int i = 0; i < n; i++) {
		swap(perm[i], perm[getRand(i, n-1)]);
		//add values to seg tree in random order for better testing
		ist.update(perm[i], arr[perm[i]]);
	}

	while(q--) {
		int type;
		cin >> type;
		if(type == 0) {
			int p, x;
			cin >> p >> x;
			ist.update(p,x);
		} else {
			int l,r;
			cin >> l >> r;
			cout << ist.query(l,r-1) << endl;
		}
	}
	return 0;
}
