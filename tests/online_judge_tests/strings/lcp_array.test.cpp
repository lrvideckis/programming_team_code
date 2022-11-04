#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"
#include "../template.hpp"

#include "../../../library/strings/suffix_array.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin >> s;
	int n = ssize(s);
	suffix_array str_info(s, 128);
	assert(ssize(str_info.lcp) == n);
	assert(str_info.lcp.back() == 0);
	long long res = 1LL * n * (n + 1) / 2;
	for (int i = 0; i < n - 1; i++)
		res -= str_info.lcp[i];
	cout << res << '\n';
}
