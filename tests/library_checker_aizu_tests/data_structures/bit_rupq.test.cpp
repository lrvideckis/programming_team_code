#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E"
#include "../template.hpp"

#include "../../../library/data_structures/binary_indexed_tree/range_update_point_query.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    bit_rupq<long long> bit_i_1(n);
    bit_rupq<long long> bit_i_2(vector<long long>(n, 50));
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int le, ri, x;
            cin >> le >> ri >> x;
            le--;
            bit_i_1.update(le, ri, x);
            bit_i_2.update(le, ri, x);
            //test degenerate updates
            bit_i_1.update(le, le, x);
            bit_i_1.update(ri, ri, x);
            bit_i_2.update(le, le, x);
            bit_i_2.update(ri, ri, x);
        } else {
            int idx;
            cin >> idx;
            idx--;
            long long res = bit_i_1.get_index(idx);
            assert(res == bit_i_2.get_index(idx) - 50);
            cout << res << '\n';
        }
    }
    return 0;
}
