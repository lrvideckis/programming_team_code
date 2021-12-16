#include "../template.h"

#include "../../random.h"
#include "../../content/range_data_structures/kthSmallest.h"

int main() {
	int n = getRand(1, 1000);
	vector<int> arr(n);
	for(int i = 0; i < n; i++) {
		arr[i] = getRand(-1000, 1000);
	}
	kthSmallest st(arr);
	for(int iterations = 1000; iterations--;) {
		int L = getRand(0,n-1), R = getRand(0,n-1);
		if(L > R) swap(L,R);
		vector<int> subarr(R-L+1);
		copy(arr.begin()+L, arr.begin()+R+1, subarr.begin());
		sort(subarr.begin(), subarr.end());
		for(int k = 1; k <= R-L+1; k++) {
			assert(st.find_kth(L,R,k) == subarr[k-1]);
		}
	}
	cout << "Tests passed!" << endl;
	return 0;
}
