#include "../test_utilities/template.h"
#include "../test_utilities/random.h"

#include "../../content/stringAlgs/suffixArray.h"

int main() {
	for(int tests = 20; tests--;) {
		int n = getRand(1, 1000);
		string s(n, 'a');
		for(int i = 0; i < n; i++) {
			s[i] = getRand(0, 2) + 'a';
		}

		suffix_array sa(s);


		vector<int> SuffixArrayNaive(n);
		for(int i = 0; i < n; i++) SuffixArrayNaive[i] = i;
		sort(SuffixArrayNaive.begin(), SuffixArrayNaive.end(), [&](int i, int j) {
				return s.substr(i) < s.substr(j);
				});

		assert(sa.get_suffix_array() == SuffixArrayNaive);
		cout << "suffix array is correct" << endl;

		vector<int> lcpNaive(n, 0);
		for(int i = 1; i < n; i++) {
			int p1 = SuffixArrayNaive[i-1];
			int p2 = SuffixArrayNaive[i];
			int len = 0;
			while(max(p1,p2) < n && s[p1] == s[p2]) {
				p1++, p2++, len++;
			}
			lcpNaive[i-1] = len;
		}

		assert(sa.get_lcp_array() == lcpNaive);
		cout << "lcp array is correct" << endl;

		for(int iter = 5000; iter--;) {
			int p1 = getRand(0, n-1), p2 = getRand(0, n-1);
			bool lessNaive = (s.substr(p1) < s.substr(p2));
			assert(lessNaive == sa.less(p1, p2));
		}
		cout << "less queries are correct" << endl;

		for(int iter = 5000; iter--;) {
			int p1 = getRand(0, n-1), p2 = getRand(0, n-1);
			if(getRand(1,100) == 1) p2 = p1;
			int fastLen = sa.longest_common_prefix(p1, p2);
			int naiveLen = 0;
			while(max(p1,p2) < n && s[p1] == s[p2]) {
				p1++, p2++, naiveLen++;
			}
			assert(naiveLen == fastLen);
		}
		cout << "longest common prefix queries are correct" << endl;
	}

	cout << "Tests passed!" << endl;
	return 0;
}
