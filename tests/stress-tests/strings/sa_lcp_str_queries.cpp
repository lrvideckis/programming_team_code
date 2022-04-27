#include "../../template.h"
#include "../test_utilities/generators/random.h"

#include "../../../Library/strings/string_queries.h"

int main() {
	for(int tests = 20; tests--;) {
		int n = getRand(1, 1000);
		string s(n, 'a');
		for(int i = 0; i < n; i++) {
			s[i] = getRand(0, 2) + 'a';
		}

		vector<int> sa_fast = sa_is(s, 255);

		{
			vector<int> sa_naive(n);
			for(int i = 0; i < n; i++) sa_naive[i] = i;
			sort(sa_naive.begin(), sa_naive.end(), [&](int i, int j) {
				return s.substr(i) < s.substr(j);
			});

			assert(sa_fast == sa_naive);
			cout << "suffix array is correct" << endl;
		}

		vector<int> lcp_fast = lcp_array(s, sa_fast);

		{
			vector<int> lcpNaive(n, 0);
			for(int i = 1; i < n; i++) {
				int p1 = sa_fast[i-1];
				int p2 = sa_fast[i];
				int len = 0;
				while(max(p1,p2) < n && s[p1] == s[p2]) {
					p1++, p2++, len++;
				}
				lcpNaive[i-1] = len;
			}

			assert(lcp_fast == lcpNaive);
			cout << "lcp array is correct" << endl;
		}

		str_queries str_qs(s);

		for(int iter = 5000; iter--;) {
			int p1 = getRand(0, n-1), p2 = getRand(0, n-1);
			bool lessNaive = (s.substr(p1) < s.substr(p2));
			assert(lessNaive == str_qs.less(p1, p2));
		}
		cout << "less queries are correct" << endl;

		for(int iter = 5000; iter--;) {
			int p1 = getRand(0, n-1), p2 = getRand(0, n-1);
			if(getRand(1,100) == 1) p2 = p1;
			int fastLen = str_qs.longest_common_prefix(p1, p2);
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
