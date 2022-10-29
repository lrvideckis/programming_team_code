#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "../template.hpp"

#include "../../../library/strings/suffix_array.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin >> s;
	for (int i : suffix_array(s, 256))
		cout << i << " ";
	cout << endl;
	return 0;
}
