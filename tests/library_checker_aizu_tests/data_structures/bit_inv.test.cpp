#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E"
#include "../template.hpp"

#include "../../../library/data_structures/binary_indexed_tree/range_update_point_query.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    bit_inv<long long> bit_i(n);
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int le, ri, x;
            cin >> le >> ri >> x;
            le--;
            bit_i.update(le, ri, x);
        } else {
            int idx;
            cin >> idx;
            idx--;
            cout << bit_i.get_index(idx) << '\n';
        }
    }
    return 0;
}
