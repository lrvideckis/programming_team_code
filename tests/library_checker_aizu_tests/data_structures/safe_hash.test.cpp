#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"
#include "../template.hpp"

#include "../../../library/data_structures/safe_hash.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            long long k, v;
            cin >> k >> v;
            safe_map[k] = v;
            safe_hash_table[k] = v;
        } else {
            assert(type == 1);
            long long k;
            cin >> k;
            assert(safe_map[k] == safe_hash_table[k]);
            cout << safe_map[k] << '\n';
        }
    }
}
