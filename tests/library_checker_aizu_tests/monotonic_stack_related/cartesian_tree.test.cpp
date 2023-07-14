#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"
#include "../template.hpp"

#include "../../../library/monotonic_stack_related/cartesian_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    auto [le, ri] = get_range(arr);
    auto [root, adj] = min_cartesian_tree(arr, le, ri);
    vector<int> par(n, -1);
    par[root] = root;
    for (int i = 0; i < n; i++) {
        assert(-1 <= le[i] && le[i] < i && i < ri[i] && ri <= n);
        assert(le[i] == -1 || arr[le[i]] < arr[i]);//because distinct numbers, if dups, then arr[le[i]] <= arr[i]
        assert(ri[i] == n || arr[i] > arr[ri[i]]);
        for (int j : adj[i]) {
            assert(le[i] <= le[j] && ri[j] <= ri[i]);
            par[j] = i;
        }
    }
    for (int i = 0; i < n; i++) cout << par[i] << " ";
    return 0;
}
