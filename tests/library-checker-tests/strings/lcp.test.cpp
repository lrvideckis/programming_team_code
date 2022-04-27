#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"
#include "../../template.h"

#include "../../../Library/strings/suffix_array.h"
#include "../../../Library/strings/longest_common_prefix.h"

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

	vector<int> lcp = lcp_array(arr, sa);

	long long res = 1LL * n * (n+1) / 2;
	for(int val : lcp) res -= val;
	cout << res << endl;

	return 0;
}
