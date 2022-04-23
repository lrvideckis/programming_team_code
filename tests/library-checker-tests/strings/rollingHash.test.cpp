#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "../../stress-tests/test_utilities/template.h"

#include "../../../Library/stringAlgs/rollingHash.h"

int main() {
	cin.tie(0)->sync_with_stdio(false);

	string s;
	cin >> s;

	int n = s.size();

	Hash<string> h(s);

	for(int i = 0; i < n; i++) {
		int start = 0, end = n+1;
		while(start+1 < end) {
			int mid = (start+end)/2;//represents length of prefix to check
			if(i+mid-1 >= n) {
				end = mid;
				continue;
			}
			if(h.getHashes(0, mid-1) == h.getHashes(i, i+mid-1)) start = mid;
			else end = mid;
		}
		cout << start << " ";
	}
	cout << endl;
	return 0;
}
