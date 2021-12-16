#include "../template.h"

#include "../../random.h"
#include "../../content/stringAlgs/rollingHash.h"

int main() {
	for(int tests = 20; tests--;) {
		int n = getRand(1, 10000);
		string s(n, 'a');
		for(int i = 0; i < n; i++) {
			s[i] = getRand(0, 3) + 'a';
		}

		Hash h(s);

		for(int iter = 5000; iter--;) {
			int L = getRand(0, n-1), R = getRand(0, n-1), lenL = getRand(1, 10);
			int lenR = lenL;
			if(getRand(1,100) == 1) lenR = getRand(1, n);
			lenL = min(lenL, n-L);
			lenR = min(lenR, n-R);
			bool naiveEqual = (s.substr(L, lenL) == s.substr(R, lenR));
			bool fastEqual = (h.getHashes(L, L+lenL-1) == h.getHashes(R, R+lenR-1));
			assert(naiveEqual == fastEqual);
		}
	}

	cout << "Tests passed!" << endl;
	return 0;
}
