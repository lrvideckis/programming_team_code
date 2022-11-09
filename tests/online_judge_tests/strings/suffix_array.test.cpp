#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "../template.hpp"

#include "../../../library/strings/suffix_array.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	{
		string s;
		suffix_array sa(s, 128);
		assert(sa.lcp.empty());
	}
	string s;
	s.reserve(500'000);
	cin >> s;
	int n = ssize(s);
	suffix_array str_info(s, 128);
	assert(ssize(str_info.sa) == n);
	assert(ssize(str_info.rank) == n);
	for (int i = 0; i < n; i++) {
		assert(str_info.sa[str_info.rank[i]] == i);
		assert(str_info.rank[str_info.sa[i]] == i);
	}
	for (int i = 0; i < n; i++)
		cout << str_info.sa[i] << " ";
	cout << '\n';
}
