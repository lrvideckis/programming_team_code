#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "../../template.h"
#include "../../random.h"

#include "../../../library/strings/kmp.h"

int main() {
	for (int tests = 20; tests--;) {
		int n = get_rand(1, 6);
		string needle(n, 'a');
		vector<int> needle_arr(n);
		for (int i = 0; i < n; i++) {
			needle_arr[i] = get_rand(0, 4);
			needle[i] = needle_arr[i] + 'a';
		}
		int m = get_rand(n, 10000);
		string haystack(m, 'a');
		vector<int> haystack_arr(m);
		for (int i = 0; i < m; i++) {
			haystack_arr[i] = get_rand(0, 4);
			haystack[i] = haystack_arr[i] + 'a';
		}
		vector<int> matches_naive;
		for (int i = 0; i <= (int)haystack.size() - (int)needle.size(); i++) {
			if (needle == haystack.substr(i, needle.size()))
				matches_naive.push_back(i);
		}
		KMP kmp(needle);
		KMP kmp_arr(needle_arr);
		assert(matches_naive == kmp.find(haystack));
		assert(matches_naive == kmp_arr.find(haystack_arr));
		vector<int> first_match = kmp.find(haystack, 0);
		vector<int> first_match_arr = kmp_arr.find(haystack_arr, 0);
		while (matches_naive.size() > 1) matches_naive.pop_back();
		assert(matches_naive == first_match);
		assert(matches_naive == first_match_arr);
	}
	int a, b;
	cin >> a >> b;
	cout << a + b << endl;
	return 0;
}
