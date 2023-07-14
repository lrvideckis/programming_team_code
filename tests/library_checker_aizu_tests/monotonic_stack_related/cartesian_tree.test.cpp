#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"
#include "../template.hpp"

#include "../../../library/monotonic_stack_related/cartesian_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    auto [root, adj] = min_cartesian_tree(arr);
    vector<int> par(n, -2);
    par[root] = root;
    for (int i = 0; i < n; i++) {
        for (int j : adj[i])
            par[j] = i;
    }
    for (int i = 0; i < n; i++) cout << par[i] << " ";
    return 0;
}
