#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"
#include "../../template.hpp"

#include "../../../library/strings/binary_trie.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int q;
	cin >> q;
	binary_trie bt;
	while (q--) {
		int type;
		long long x;
		cin >> type >> x;
		if (type == 0) {
			if (bt.update(x, 0) == 0) bt.update(x, 1);
		} else if (type == 1) {
			if (bt.update(x, 0) == 1) bt.update(x, -1);
		} else {
			assert(type == 2);
			long long val = bt.min_xor(x);
			cout << (val ^ x) << endl;
		}
	}
	return 0;
}
