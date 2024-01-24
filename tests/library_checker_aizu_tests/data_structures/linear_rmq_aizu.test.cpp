#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A"
#include "../template.hpp"

#include "../../../library/data_structures/uncommon/linear_rmq.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<int> init(n, INT_MAX);
    linear_rmq lin_rmq(init, less());
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int idx, val;
            cin >> idx >> val;
            lin_rmq.update(idx, val);
        } else {
            assert(type == 1);
            int le, ri;
            cin >> le >> ri;
            ri++;
            cout << lin_rmq.query(le, ri) << '\n';
        }
    }
}
