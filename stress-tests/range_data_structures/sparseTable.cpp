#include "../test_utilities/template.h"
#include "../test_utilities/random.h"

#include "../../content/range_data_structures/sparseTable.h"

int main() {
	for(int tests = 20; tests--;) {
		int n = getRand(1, 1000);
		vector<ll> arr(n);
		int mx = 1e9;
		for(int i = 0; i < n; i++) {
			arr[i] = getRand(-mx, mx);
		}
		sparseTableIdx<ll> stIdx(arr);
		sparseTable st(arr);
		for(int i = 0; i < n; i++) {
			int mnIdx = i;
			for(int j = i; j < n; j++) {
				if(arr[mnIdx] > arr[j]) mnIdx = j;
				assert(stIdx.query(i,j) == mnIdx);
				assert(st.query(i,j) == arr[mnIdx]);
			}
		}
	}
	cout << "Tests passed!" << endl;
	return 0;
}
