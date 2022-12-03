#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_B"
#include "../template.hpp"
#include "../kactl_macros.hpp"

#include "../../../library/strings/knuth_morris_pratt.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string haystack, needle;
	cin >> haystack >> needle;
	KMP kmp(needle);
	for (int idx : kmp.find(haystack))
		cout << idx << "\n";
	return 0;
}
