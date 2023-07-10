#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../template.hpp"

#include "../../../library/data_structures/sparse_table.hpp"
#include "../../../library/data_structures/uncommon_data_structures/disjoint_sparse_table.hpp"
#include "../../../library/data_structures/uncommon_data_structures/linear_rmq.hpp"
#include "../../../library/monotonic_stack_related/monotonic_stack.hpp"

int mn(int x, int y) {
    return min(x, y);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    {
        RMQ rmq_without_template(vector<int>(), mn);
        disjoint_rmq disjoint_rmq_without_template(vector<int>(), mn);
        linear_rmq lin_rmq_without_template(vector<int>(), less<int>());
    }
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    RMQ<int> rmq(arr, [](auto x, auto y) {return min(x, y);});
    disjoint_rmq<int> dis_rmq(arr, [](auto x, auto y) {return min(x, y);});
    linear_rmq<int> lin_rmq(arr, less<int>());
    vector<int> le_mono = monotonic_stack<int>(arr, less());
    vector<int> ri_mono = monotonic_stack<int>(vector<int>(rbegin(arr), rend(arr)), less());
    auto rv = [&](int i) -> int {
        return n - 1 - i;
    };
    while (q--) {
        int le, ri;
        cin >> le >> ri;
        int idx_min = lin_rmq.query_idx(le, ri);
        assert(le_mono[idx_min] < le && le <= idx_min && idx_min < ri && ri <= rv(ri_mono[rv(idx_min)]));
        assert(rmq.query(le_mono[idx_min] + 1, rv(ri_mono[rv(idx_min)])) == arr[idx_min]);
        assert(arr[idx_min] == rmq.query(le, ri));
        assert(arr[idx_min] == dis_rmq.query(le, ri));
        assert(arr[idx_min] == lin_rmq.query(le, ri));
        cout << arr[idx_min] << '\n';
    }
}
