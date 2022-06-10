#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"
#include "../../template.h"

#include "../../../library/strings/suffix_array.h"
#include "../../../library/strings/lcp.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);

	string s;
	cin >> s;

	vector<int> sa = sa_is(s, 255);

	vector<int> lcp = LCP(s, sa);

	int n = s.size();
	long long res = 1LL * n * (n+1) / 2;
	for(int val : lcp) res -= val;
	cout << res << endl;

	return 0;
}
