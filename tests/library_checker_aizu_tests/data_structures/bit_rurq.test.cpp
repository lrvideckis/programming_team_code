#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G"
#include "../template.hpp"

#include "../../../library/data_structures/binary_indexed_tree/rurq.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q;
    cin >> n >> q;
    bit_rurq<long long> bit(n);
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int le, ri, x;
            cin >> le >> ri >> x;
            le--;
            bit.update(le, ri, x);
            //test degenerate update
            bit.update(le, le, x);
            bit.update(ri, ri, x);
        } else {
            int le, ri;
            cin >> le >> ri;
            le--;
            cout << bit.sum(le, ri) << '\n';
        }
    }
    return 0;
}
