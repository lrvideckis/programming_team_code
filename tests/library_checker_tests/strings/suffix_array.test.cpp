#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "../../template.h"

#include "../../../library/strings/suffix_array.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);

	string s;
	cin >> s;

	vector<int> sa = sa_is(s, 255);

	for(int val : sa) {
		cout << val << " ";
	}
	cout << endl;

	return 0;
}
