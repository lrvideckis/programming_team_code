#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "../template.hpp"

#include "../../../library/data_structures/sparse_table.hpp"
#include "../../../library/data_structures/uncommon_data_structures/disjoint_sparse_table.hpp"
#include "../../../library/data_structures/uncommon_data_structures/linear_rmq.hpp"
#include "../../../library/monotonic_stack_related/monotonic_range.hpp"

int mn(int x, int y) {
    return min(x, y);
}

bool cmp(int x, int y) {
    return x < y;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    {
        RMQ rmq_without_template(vector<int>(), mn);
        disjoint_rmq disjoint_rmq_without_template(vector<int>(), mn);
        linear_rmq lin_rmq_without_template(vector<int>(), cmp);
    }
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    RMQ rmq(arr, [](auto x, auto y) {return min(x, y);});
    disjoint_rmq dis_rmq(arr, [](auto x, auto y) {return min(x, y);});
    linear_rmq lin_rmq(arr, less());
    auto [le_mono, ri_mono] = mono_range(arr, less_equal());
    for (int i = 0; i < n; i++) {
        assert(le_mono[i] == -1 || arr[le_mono[i]] <= arr[i]);
        assert(ri_mono[i] == n || arr[i] > arr[ri_mono[i]]);
    }
    while (q--) {
        int le, ri;
        cin >> le >> ri;
        int idx_min = lin_rmq.query_idx(le, ri);
        assert(le_mono[idx_min] < le && le <= idx_min && idx_min < ri && ri <= ri_mono[idx_min]);
        assert(rmq.query(le_mono[idx_min] + 1, ri_mono[idx_min]) == arr[idx_min]);
        auto curr_1 = rmq.query(le, ri);
        assert(arr[idx_min] == curr_1);
        auto curr_2 = dis_rmq.query(le, ri);
        assert(arr[idx_min] == curr_2);
        auto curr_3 = lin_rmq.query(le, ri);
        assert(arr[idx_min] == curr_3);
        cout << arr[idx_min] << '\n';
    }
}
