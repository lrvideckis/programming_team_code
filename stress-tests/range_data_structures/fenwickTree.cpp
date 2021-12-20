#include "../test_utilities/template.h"
#include "../test_utilities/random.h"

#include "../../content/range_data_structures/fenwickTree.h"

int main() {
	for(int tests = 20; tests--;) {
		{
			int n = getRand(1, 1000);
			vector<ll> arr(n);
			int mx = 1e9;
			for(int i = 0; i < n; i++) {
				arr[i] = getRand(-mx, mx);
			}
			fenwickTree ft(0);
			if(getRand(1,2) == 1) {
				cout << "constructor 1" << endl;
				ft = fenwickTree(arr);
			} else {
				cout << "constructor 2" << endl;
				ft = fenwickTree(n);
				arr = vector<ll>(n, 0);
			}
			for(int iterations = 5000; iterations--;) {
				if(getRand(1,2) == 1) {//update
					int idx = getRand(0, n-1);
					ll diff = getRand(-mx, mx);
					ft.update(idx, diff);
					arr[idx] += diff;
				} else {//query
					int L = getRand(0,n-1), R = getRand(0,n-1);
					if(L > R) swap(L,R);
					ll sum = arr[L];
					for(int i = L+1; i <= R; i++) {
						sum += arr[i];
					}
					assert(ft.sum(L,R) == sum);
				}
			}
		}
		{
			int n = getRand(1, 1000);
			vector<ll> arr(n);
			int mx = 1e9;
			for(int i = 0; i < n; i++) {
				arr[i] = getRand(-mx, mx);
			}
			rangeUpdatesAndPointQueries ft(arr);
			for(int iterations = 5000; iterations--;) {
				if(getRand(1,2) == 1) {//update
					int L = getRand(0,n-1), R = getRand(0,n-1);
					if(L > R) swap(L,R);
					ll diff = getRand(-mx, mx);
					ft.updateRange(L, R, diff);
					for(int i = L; i <= R; i++) {
						arr[i] += diff;
					}
				} else {//query
					int idx = getRand(0, n-1);
					assert(ft.queryIdx(idx) == arr[idx]);
				}
			}
		}
	}
	cout << "Tests passed!" << endl;
	return 0;
}
