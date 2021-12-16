#include "../template.h"

#include "../../random.h"
#include "../../content/stringAlgs/kmp.h"

int main() {
	int n = getRand(1, 10);
	string needle(n, 'a');
	for(int i = 0; i < n; i++) {
		needle[i] = getRand(0, 3) + 'a';
	}

	int m = getRand(n, 10000);
	string haystack(m, 'a');
	for(int i = 0; i < m; i++) {
		haystack[i] = getRand(0, 3) + 'a';
	}

	vector<int> matchesNaive;
	for(int i = 0; i <= (int)haystack.size() - (int)needle.size(); i++) {
		if(needle == haystack.substr(i, needle.size())) {
			matchesNaive.push_back(i);
		}
	}
	KMP_Match kmp(needle);
	assert(matchesNaive == kmp.find(haystack));

	vector<int> firstMatch = kmp.find(haystack, false);
	while(matchesNaive.size() > 1) matchesNaive.pop_back();
	assert(matchesNaive == firstMatch);




	cout << "Tests passed!" << endl;
	return 0;
}
