#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_D"
#include "../template.hpp"
#include "../kactl_macros.hpp"

#include "../../../library/strings/longest_common_prefix_query.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin >> s;
	lcp_query lcp_q(s);
	int q;
	cin >> q;
	while (q--) {
		string t;
		cin >> t;
		auto [le, ri] = lcp_q.find(t);
		cout << (!!(ri - le > 0)) << '\n';
	}
	return 0;
}
