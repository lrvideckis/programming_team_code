#include "../test_utilities/template.h"
#include "../test_utilities/random.h"

#include "../../content/stringAlgs/kmp.h"

int main() {
	for(int tests = 20; tests--;) {
		int n = getRand(1, 5);
		string needle(n, 'a');
		vector<int> needleArr(n);
		for(int i = 0; i < n; i++) {
			needleArr[i] = getRand(0, 3);
			needle[i] = needleArr[i] + 'a';
		}

		int m = getRand(n, 10000);
		string haystack(m, 'a');
		vector<int> haystackArr(m);
		for(int i = 0; i < m; i++) {
			haystackArr[i] = getRand(0,3);
			haystack[i] = haystackArr[i] + 'a';
		}

		vector<int> matchesNaive;
		for(int i = 0; i <= (int)haystack.size() - (int)needle.size(); i++) {
			if(needle == haystack.substr(i, needle.size())) {
				matchesNaive.push_back(i);
			}
		}
		cout << "number of matches: " << matchesNaive.size() << endl;
		KMP_Match<string> kmp(needle);
		KMP_Match<vector<int>> kmpArr(needleArr);
		assert(matchesNaive == kmp.find(haystack));
		assert(matchesNaive == kmpArr.find(haystackArr));

		vector<int> firstMatch = kmp.find(haystack, false);
		vector<int> firstMatchArr = kmpArr.find(haystackArr, false);
		while(matchesNaive.size() > 1) matchesNaive.pop_back();
		assert(matchesNaive == firstMatch);
		assert(matchesNaive == firstMatchArr);
	}

	cout << "Tests passed!" << endl;
	return 0;
}
