#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_B"
//since this causes an O(n) partition check for each call to `lower_bound`,
//causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"
#include "../kactl_macros.hpp"

#include "../../../library/strings/suffix_array_query.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s, t;
	cin >> s >> t;
	sa_query sq(s, 128);
	auto [le, ri] = sq.find(t);
	vector<int> matches;
	for (int i = le; i < ri; i++)
		matches.push_back(sq.info.sa[i]);
	sort(matches.begin(), matches.end());
	{
		int first_match = sq.find_first(t);
		if (matches.empty())
			assert(first_match == -1);
		else {
			assert(first_match == matches[0]);
			assert(t == s.substr(first_match, ssize(t)));
		}
	}
	for (int match : matches)
		cout << match << '\n';
	return 0;
}
