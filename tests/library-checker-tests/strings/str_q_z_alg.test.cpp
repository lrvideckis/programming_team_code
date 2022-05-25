#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "../../template.h"

#include "../../../Library/strings/lcp_queries.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);

	string s;
	cin >> s;

	lcp_queries sq(s);

	for(int i = 0; i < (int) s.size(); i++) {
		cout << sq.longest_common_prefix(i, 0) << " ";
	}
	cout << endl;

	return 0;
}
