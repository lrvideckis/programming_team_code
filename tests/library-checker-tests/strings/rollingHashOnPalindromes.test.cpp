#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include "../../template.h"

#include "../../../Library/strings/rollingHash.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);

	string s;
	cin >> s;

	int n = s.size();

	string rev(s);
	reverse(rev.begin(), rev.end());

	Hash hash(s), revHash(rev);

	for(int i = 0; i < n; i++) {
		for(int j : {i, i+1}) {
			if(j >= n) continue;
			int start = 0, end = n+1;
			while(start + 1 < end) {
				int mid = (start+end)/2;
				if(j+mid-1 < n && i-mid+1 >= 0 && hash(j, j+mid-1) == revHash(n-1-(i), n-1-(i-mid+1)))
					start = mid;
				else
					end = mid;
			}
			if(i == j) {//odd length
				cout << 2 * start - 1 << " ";//subtract 1 to not double-count middle character
			} else {
				cout << 2 * start << " ";
			}
		}
	}
	cout << endl;

	return 0;
}
