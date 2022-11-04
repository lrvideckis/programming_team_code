#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include "../template.hpp"
#include "../kactl_macros.hpp"

#include "../../../library/strings/suffix_array_query.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin >> s;
	int n = ssize(s);
	s = s + '$' + string(s.rbegin(), s.rend());
	sa_query sq(s, 128);
	for (int i = 0; i < n; i++) {
		for (int j = i; j < min(i + 2, n); j++)
			cout << sq.get_lcp(j, (n - i - 1) + n + 1) * 2 - (i == j) << " ";
	}
	cout << endl;
	return 0;
}
