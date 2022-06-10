#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"
#include "../../template.h"

#include "../../../library/misc/monotonic_stack.h"
#include "../../../library/range_data_structures/RMQ.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;

	vector<int> arr(n);
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	RMQ<int> st(arr, [](int x, int y) { return min(x,y); });

	vector<int> leftLower = monotonic_stack(arr);
	reverse(arr.begin(), arr.end());
	vector<int> rightLower = monotonic_stack(arr);
	reverse(arr.begin(), arr.end());

	vector<int> par(n, -1);
	for(int i = 0; i < n; i++) {
		int L = leftLower[i], R = n-1-rightLower[n-1-i];
		assert(0 <= L+1 && L+1 <= i && i <= R-1 && R-1 < n);
		if(L+1 < i) assert(st.query(L+1, i-1) > arr[i]);
		if(i < R-1) assert(st.query(i+1, R-1) > arr[i]);
		if(L >= 0) assert(arr[L] <= arr[i]);
		if(R < n) assert(arr[R] <= arr[i]);

		if(L == -1 && R == n) par[i] = i;
		else if(L == -1) par[i] = R;
		else if(R == n) par[i] = L;
		else par[i] = arr[L] > arr[R] ? L : R;
	}

	for(int i = 0; i < n; i++) {
		cout << par[i] << " ";
	}

	return 0;
}
