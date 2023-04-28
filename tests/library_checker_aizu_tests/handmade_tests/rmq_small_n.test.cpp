#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/misc/random.hpp"

#include "../../../library/data_structures/sparse_table.hpp"
#include "../../../library/data_structures/uncommon_data_structures/disjoint_sparse_table.hpp"
#include "../../../library/data_structures/uncommon_data_structures/linear_rmq.hpp"

void test_all_subarrays(const vector<int>& arr) {
    int n = ssize(arr);
    RMQ rmq(arr, [](auto x, auto y) {return min(x, y);});
    disjoint_rmq dis_rmq(arr, [](auto x, auto y) {return min(x, y);});
    linear_rmq lin_rmq(arr, less());
    for (int le = 0; le < n; le++) {
        for (int ri = le + 1; ri <= n; ri++) {
            int idx_min = lin_rmq.query_idx(le, ri);
            assert(le <= idx_min && idx_min < ri);
            assert(arr[idx_min] == rmq.query(le, ri));
            assert(arr[idx_min] == dis_rmq.query(le, ri));
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int n = 1; n <= 8; n++) {
        vector<int> perm(n);
        iota(begin(perm), end(perm), 0);
        do {
            test_all_subarrays(perm);
        } while (next_permutation(begin(perm), end(perm)));
    }
    for (int n = 1; n <= 100; n++) {
        for (int times = 0; times < 40; times++) {
            vector<int> arr(n);
            for (int i = 0; i < n; i++) arr[i] = get_rand<int>(INT_MIN, INT_MAX);
            test_all_subarrays(arr);
        }
    }
    cout << "Hello World\n";
}
