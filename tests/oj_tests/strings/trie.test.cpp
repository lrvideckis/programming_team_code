#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_4_C"
#include "../../template.hpp"

#include "../../../library/strings/trie.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	trie tr;
	for (int i = 0; i < n; i++) {
		string type, s;
		cin >> type >> s;
		if (type == "insert")
			tr.add_string(s);
		else
			cout << (tr.find_string(s) ? "yes" : "no") << '\n';
	}
	return 0;
}
