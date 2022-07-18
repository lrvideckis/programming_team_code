#include "../../template.h"
#include "../../random.h"

#include "../../../library/range_data_structures/seg_tree.h"

int main() {
	const int mx_val = 1e9;
	for(int tests = 50; tests--;) {
		int n = getRand(1, 1000);
		vector<long long> arr(n);
		for(int i = 0; i < n; i++)
			arr[i] = getRand(-mx_val, mx_val);

		seg_tree st(arr);

		for(int iterations = 5000; iterations--;) {
			int L = getRand(0,n), R = getRand(0,n);
			if(L > R) swap(L,R);
			if(getRand(1,2) == 1) {//update
				long long diff = getRand(-mx_val, mx_val);
				if(getRand(1,2) == 1) st.update(L, R, diff);//iterative version
				else st.update(1, L, R, diff);//recursive versoin
				for(int i = L; i < R; i++) arr[i] += diff;
			} else {//query
				long long sum = 0, mx = -1e18, mn = 1e18;
				for(int i = L; i < R; i++) {
					sum += arr[i];
					mx = max(mx, arr[i]);
					mn = min(mn, arr[i]);
				}
				seg_tree::dt naive = {sum, mx, mn};
				if(getRand(1,2) == 1) assert(naive == st.query(L, R));//iterative version
				else assert(naive == st.query(1, L, R));//recursive version
			}
		}
	}
	cout << "Tests passed!" << endl;
	return 0;
}
