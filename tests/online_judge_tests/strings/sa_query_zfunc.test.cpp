#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "../template.hpp"
#include "../kactl_macros.hpp"
#include "../../../library/misc/random.hpp"

#include "../../../library/strings/suffix_array_query.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s;
	s.reserve(500'000);
	cin >> s;
	sa_query sq(s, 128);
	//test `less` function
	{
		for (int num_tests = 50; num_tests--;) {
			auto le = get_rand<int>(0, ssize(s));
			auto ri = get_rand<int>(0, ssize(s));
			if (le > ri)
				swap(le, ri);
			assert(sq.less(le, ri) == (s.substr(le) < s.substr(ri)));
		}
	}
	for (int i = 0; i < ssize(s); i++)
		cout << sq.get_lcp(i, 0) << " ";
	cout << endl;
	return 0;
}
