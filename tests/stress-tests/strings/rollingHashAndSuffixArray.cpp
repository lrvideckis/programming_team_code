#include "../../template.h"
#include "../test_utilities/generators/random.h"

#include "../../../Library/strings/rollingHash.h"
#include "../../../Library/strings/string_queries.h"

int main() {
	for(int tests = 50; tests--;) {
		int n = getRand(1, 50);
		string s(n, 'a');
		vector<int> arr(n);
		for(int i = 0; i < n; i++) {
			arr[i] = getRand(1, 4);
			s[i] = arr[i] + 'a';
		}

		str_queries sa(s);

		Hash hStr(s);
		Hash hArr(arr);

		for(int i = 0; i < n; i++) {
			for(int j = i; j < n; j++) {
				bool sameNaive = true;
				for(int len = 1; j+len-1 < n; len++) {
					if(s[i+len-1] != s[j+len-1]) {
						sameNaive = false;
					}
					bool sameHashStr = hStr.getHashes(i,i+len-1) == hStr.getHashes(j,j+len-1);
					bool sameHashArr = hArr.getHashes(i,i+len-1) == hArr.getHashes(j,j+len-1);
					bool sameSA = len <= sa.longest_common_prefix(i,j);
					assert(sameNaive == sameHashStr);
					assert(sameNaive == sameHashArr);
					assert(sameNaive == sameSA);


					//sanity check on different lengths
					if(j+len < n) {
						assert(hStr.getHashes(i,i+len-1) != hStr.getHashes(i, n-1));
						assert(hArr.getHashes(i,i+len-1) != hArr.getHashes(i, n-1));
					}
					if(len > 1) {
						assert(hStr.getHashes(i,i+len-1) != hStr.getHashes(i,i));
						assert(hArr.getHashes(i,i+len-1) != hArr.getHashes(i,i));
					}
				}
			}
		}
	}

	cout << "Tests passed!" << endl;
	return 0;
}
