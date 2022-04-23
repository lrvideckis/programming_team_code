#include "test_utilities/template.h"
#include "test_utilities/random.h"

#include "../../Library/strings/rollingHash.h"
#include "../../Library/strings/suffixArray.h"

int main() {
	for(int tests = 200; tests--;) {
		int n = getRand(1, 100);
		string s(n, 'a');
		vector<int> arr(n);
		for(int i = 0; i < n; i++) {
			arr[i] = getRand(1, 4);
			s[i] = arr[i] + 'a';
		}

		suffix_array sa(s);

		Hash<string> hStr(s);
		Hash<vector<int>> hArr(arr);

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
