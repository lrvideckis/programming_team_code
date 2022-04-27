#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "../../template.h"

#include "../../../Library/strings/suffix_array.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);

	string s;
	cin >> s;

	int n = s.size();

	vector<int> arr(n);
	for(int i = 0; i < n; i++) {
		arr[i] = s[i];
	}

	vector<int> sa = sa_is(arr, 255);

	for(int val : sa) {
		cout << val << " ";
	}
	cout << endl;

	return 0;
}
