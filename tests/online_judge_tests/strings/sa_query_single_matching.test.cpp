#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_B"
#include "../template.hpp"
#include "../kactl_macros.hpp"

#include "../../../library/strings/suffix_array_query.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s, t;
	cin >> s >> t;
	sa_query sq(s);
	auto [le, ri] = sq.find(t);
	vector<int> matches;
	for(int i = le; i < ri; i++) {
		matches.push_back(sq.info.sa[i]);
	}
	sort(matches.begin(), matches.end());
	for(int match : matches)
		cout << match << '\n';
	return 0;
}
