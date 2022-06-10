#include "../../template.h"
#include "../../random.h"

#include "../../../library/range_data_structures/uncommon/buckets.h"

int main() {
	for(int tests = 20; tests--;) {
		int n = getRand(1, 1000);
		vector<int> arr(n);
		int mx = 1e3;
		for(int i = 0; i < n; i++) {
			arr[i] = getRand(-mx, mx);
		}
		buckets bckts(arr);
		for(int iterations = 5000; iterations--;) {
			int L = getRand(0,n-1), R = getRand(0,n-1);
			if(L > R) swap(L,R);
			if(getRand(1,2) == 1) {//update
				int diff = getRand(-mx, mx);
				bckts.update(L, R, diff);
				for(int i = L; i <= R; i++) arr[i] += diff;
			} else {//query
				int sum = 0;
				for(int i = L; i <= R; i++) {
					sum += arr[i];
				}
				assert(bckts.query(L, R) == sum);
			}
		}
	}
	cout << "Tests passed!" << endl;
	return 0;
}
