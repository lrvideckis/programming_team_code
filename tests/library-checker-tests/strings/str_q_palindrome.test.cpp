#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include "../../template.h"

#include "../../../Library/strings/string_queries.h"

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

	str_queries sq(s);

	for(int i = 0; i < n; i++) {
		for(int j : {i, i+1}) {
			if(j >= n) continue;
			cout << sq.longest_common_prefix(j, (n-i-1)+n+1) * 2 - (i==j) << " ";
		}
	}
	cout << endl;

	return 0;
}
