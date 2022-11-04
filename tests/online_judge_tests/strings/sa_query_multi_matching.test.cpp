#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_D"
#include "../template.hpp"
#include "../kactl_macros.hpp"

#include "../../../library/strings/suffix_array_query.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin >> s;
	sa_query sq(s, 128);
	int q;
	cin >> q;
	while (q--) {
		string t;
		cin >> t;
		auto [le, ri] = sq.find(t);
		cout << (!!(ri - le > 0)) << '\n';
	}
	return 0;
}
