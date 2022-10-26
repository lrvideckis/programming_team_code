#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "../template.hpp"
#include "../../../library/misc/random.hpp"

#include "../../../library/strings/longest_common_prefix_query.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin >> s;
	lcp_query<string> sq(s);
	//test `less` function
	{
		for (int numTests = 50; numTests--;) {
			auto le = get_rand<long long>(0, ssize(s));
			auto ri = get_rand<long long>(0, ssize(s));
			if (le > ri) swap(le, ri);
			assert(sq.less(le, ri) == (s.substr(le) < s.substr(ri)));
		}
	}
	for (int i = 0; i < ssize(s); i++)
		cout << sq.get_lcp(i, 0) << " ";
	cout << endl;
	return 0;
}
