#include "../test_utilities/template.h"
#include "../test_utilities/random.h"

#include "../../content/range_data_structures/kthSmallest.h"


int main() {
	for(int tests = 20; tests--;) {
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
			vector<ll> prefix(subarr.size()+1, 0);
			for(int i = 0; i < (int)subarr.size(); i++) {
				prefix[i+1] = prefix[i] + subarr[i];
			}
			for(int iter = R-L+1; iter--;) {
				int valL = getRand(-1000, 1000), valR = getRand(-1000, 1000);
				if(valL > valR) swap(valL, valR);
				int posL = (int)(lower_bound(subarr.begin(), subarr.end(), valL) - subarr.begin());
				int posR = (int)(upper_bound(subarr.begin(), subarr.end(), valR) - subarr.begin()) - 1;

				assert(st.cnt_in_range(L, R, valL, valR) == posR - posL + 1);
				assert(st.sum_in_range(L, R, valL, valR) == prefix[posR+1] - prefix[posL]);
			}
		}
	}
	cout << "Tests passed!" << endl;
	return 0;
}
