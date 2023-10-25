#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"
#include "../template.hpp"

#include "../../../library/data_structures/uncommon_data_structures/binary_trie.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q;
    cin >> q;
    binary_trie<int> bt;
    while (q--) {
        int type, x;
        cin >> type >> x;
        if (type == 0) {
            if (bt.update(x, 0) == 0)
                bt.update(x, 1);
        } else if (type == 1) {
            if (bt.update(x, 0) == 1)
                bt.update(x, -1);
        } else {
            assert(type == 2);
            int val = bt.min_xor(x);
            cout << (val ^ x) << '\n';
        }
    }
    return 0;
}
