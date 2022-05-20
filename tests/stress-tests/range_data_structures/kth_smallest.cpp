#include "../../template.h"
#include "../test_utilities/generators/random.h"

#include "../../../Library/range_data_structures/kth_smallest.h"
#include "../../../Library/range_data_structures/mergeSortTree.h"


int main() {
	for(int tests = 20; tests--;) {
		int n = getRand(1, 100);
		vector<int> arr(n);
		if(getRand(0,1) == 0) {
			for(int i = 0; i < n; i++) {
				arr[i] = getRand<int>(-1e9, 1e9);
			}
		} else {
			for(int i = 0; i < n; i++) {
				arr[i] = getRand<int>(-2, 2);
			}
		}
		kth_smallest st(arr);
		MergeSortTree mst(arr);
		for(int iterations = 200; iterations--;) {
			int L = getRand(0,n-1), R = getRand(0,n-1);
			if(L > R) swap(L,R);
			vector<int> subarr(R-L+1);
			copy(arr.begin()+L, arr.begin()+R+1, subarr.begin());
			sort(subarr.begin(), subarr.end());
			int numLess = 0;
			for(int k = 1; k <= R-L+1; k++) {
				assert(st.query(L,R,k) == subarr[k-1]);
				if(k-2 >= 0 && subarr[k-1] != subarr[k-2]) {
					numLess = k-1;
				}
				// MergeSortTree::query(L,R,X) returns # of numbers less than
				// X. So `numLess` is needed to handle duplicates in query range
				assert(mst.query(L, R, subarr[k-1]) == numLess);
			}
		}
	}
	cout << "Tests passed!" << endl;
	return 0;
}
