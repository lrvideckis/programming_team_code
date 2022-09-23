#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "../template.hpp"

#include "../../../library/strings/longest_common_prefix_query.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin >> s;
	lcp_query<string> sq(s);
	for (int i = 0; i < ssize(s); i++)
		cout << sq.get_lcp(i, 0) << " ";
	cout << endl;
	return 0;
}
