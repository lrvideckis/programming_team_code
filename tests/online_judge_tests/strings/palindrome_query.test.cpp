#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include "../template.hpp"
#include "../kactl_macros.hpp"

#include "../../../library/misc/random.hpp"
#include "../../../library/strings/palindrome_query.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin >> s;
	int n = ssize(s);
	pal_query pal_q(s);
	{
		vector<pair<int, int>> tests;
		for (int i = 0; i < n; i++) {
			for (int j = i; j <= min(n, i + int(1e7 / n)); j++)
				tests.emplace_back(i, j);
		}
		for (int i = 0; i < int(1e7 / n); i++) {
			int l = get_rand(0, n), r = get_rand(0, n);
			if (l > r) swap(l, r);
			tests.emplace_back(l, r);
		}
		for (auto [l, r] : tests) {
			string substr = s.substr(l, r - l);
			assert(pal_q.is_pal(l, r) == (substr == string(substr.rbegin(), substr.rend())));
		}
	}
	for (int i = 0; i < n; i++) {
		cout << 2 * pal_q.pal_len[1][i] + 1 << " ";
		if (i + 1 < n)
			cout << 2 * pal_q.pal_len[0][i + 1] << " ";
	}
	return 0;
}
