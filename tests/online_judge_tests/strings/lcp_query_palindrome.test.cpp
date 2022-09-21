#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include "../template.hpp"

#include "../../../library/strings/longest_common_prefix_query.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin >> s;
	int n = s.size();
	s = s + '$' + string(s.rbegin(), s.rend());
	lcp_query lcp_q(s);
	for (int i = 0; i < n; i++) {
		for (int j = i; j < min(i + 2, n); j++)
			cout << lcp_q.get_lcp(j, (n - i - 1) + n + 1) * 2 - (i == j) << " ";
	}
	cout << endl;
	return 0;
}
