#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../template.hpp"

#include "../../../library/data_structures/binary_indexed_tree/binary_indexed_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<long long> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    BIT<long long> bit(arr);
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int p, x;
            cin >> p >> x;
            bit.update(p, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << bit.sum(l, r) << '\n';
        }
    }
    return 0;
}
