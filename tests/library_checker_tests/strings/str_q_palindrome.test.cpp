#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include "../../template.h"

#include "../../../library/strings/pal_query.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin >> s;
	int n = s.size();
	{
		string rev(s);
		reverse(rev.begin(), rev.end());
		s = s + '$' + rev;
	}
	lcp_query sq(s);
	pal_query pal_q(s);
	for (int i = 0; i < n; i++) {
		for (int j : {
		            i, i + 1
		        }) {
			if (j >= n) continue;
			int len_half = sq.longest_common_prefix(j, 2 * n - i);
			cout << len_half * 2 - (i == j) << " ";
			if (len_half > 0) assert(pal_q.is_pal(i - len_half + 1, j + len_half));
			if (i - len_half >= 0 && j + len_half + 1 <= n) assert(!pal_q.is_pal(i - len_half, j + len_half + 1));
		}
	}
	cout << endl;
	return 0;
}
