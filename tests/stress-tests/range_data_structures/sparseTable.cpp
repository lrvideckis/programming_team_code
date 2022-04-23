#include "test_utilities/template.h"
#include "test_utilities/random.h"

#include "../../Library/range_data_structures/sparseTable.h"

int main() {
	for(int tests = 20; tests--;) {
		int n = getRand(1, 1000);
		vector<ll> arr(n);
		int mx = 1e9;
		vector<pair<ll,int>> arrIdx(n);
		for(int i = 0; i < n; i++) {
			arr[i] = getRand(-mx, mx);
			arrIdx[i] = make_pair(arr[i], i);
		}
		sparseTable<pair<ll,int>> stIdx(arrIdx, [](pair<ll,int> x, pair<ll,int> y) { return min(x,y); });
		sparseTable<ll> st(arr, [](ll x, ll y) { return min(x,y); });
		for(int i = 0; i < n; i++) {
			int mnIdx = i;
			for(int j = i; j < n; j++) {
				if(arr[mnIdx] > arr[j]) mnIdx = j;
				assert(stIdx.query(i,j).second == mnIdx);
				assert(st.query(i,j) == arr[mnIdx]);
			}
		}
	}
	cout << "Tests passed!" << endl;
	return 0;
}
