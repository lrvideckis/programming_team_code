#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"
#include "../template.hpp"

#include "../../../library/misc/monotonic_stack_related/cartesian_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> arr(n), arr_negative(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr_negative[i] = -arr[i];
    }
    vector<int> par_min = cartesian_tree(arr, less());
    vector<int> par_max = cartesian_tree(arr_negative, greater());
    assert(par_min == par_max);
    for (int i = 0; i < n; i++) {
        if (par_min[i] == -1) cout << i << " ";
        else cout << par_min[i] << " ";
    }
    return 0;
}
