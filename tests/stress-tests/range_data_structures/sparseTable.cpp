#include "../../template.h"
#include "../../random.h"

#include "../../../Library/range_data_structures/sparseTable.h"

int main() {
	for(int tests = 20; tests--;) {
		int n = getRand(1, 1000);
		vector<long long> arr(n);
		int mx = 1e9;
		vector<pair<long long,int>> arrIdx(n);
		for(int i = 0; i < n; i++) {
			arr[i] = getRand(-mx, mx);
			arrIdx[i] = make_pair(arr[i], i);
		}
		sparseTable<pair<long long,int>> stIdx(arrIdx, [](pair<long long,int> x, pair<long long,int> y) { return min(x,y); });
		sparseTable<long long> st(arr, [](long long x, long long y) { return min(x,y); });
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
