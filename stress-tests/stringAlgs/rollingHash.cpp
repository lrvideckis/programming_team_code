#include "../test_utilities/template.h"
#include "../test_utilities/random.h"

#include "../../content/stringAlgs/rollingHash.h"

int main() {
	for(int tests = 20; tests--;) {
		int n = getRand(1, 10000);
		string s(n, 'a');
		vector<int> arr(n);
		for(int i = 0; i < n; i++) {
			arr[i] = getRand(1, 4);
			s[i] = arr[i] + 'a';
		}

		Hash<string> hStr(s);
		Hash<vector<int>> hArr(arr);

		for(int iter = 50000; iter--;) {
			int L = getRand(0, n-1), R = getRand(0, n-1), lenL = getRand(1, 10);
			int lenR = lenL;
			if(getRand(1,100) == 1) lenR = getRand(1, n);
			lenL = min(lenL, n-L);
			lenR = min(lenR, n-R);
			bool naiveEqual = (s.substr(L, lenL) == s.substr(R, lenR));
			bool fastEqualStr = (hStr.getHashes(L, L+lenL-1) == hStr.getHashes(R, R+lenR-1));
			assert(naiveEqual == fastEqualStr);

			bool fastEqualArr = (hArr.getHashes(L, L+lenL-1) == hArr.getHashes(R, R+lenR-1));
			assert(naiveEqual == fastEqualArr);
		}
	}

	cout << "Tests passed!" << endl;
	return 0;
}
