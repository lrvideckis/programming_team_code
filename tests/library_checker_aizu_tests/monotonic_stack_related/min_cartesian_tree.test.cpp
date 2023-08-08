#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"
#include "../template.hpp"

#include "../../../library/monotonic_stack_related/min_cartesian_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    auto [root, adj, le, ri, to_min] = min_cartesian_tree(arr);
    vector<int> par(n, -1);
    par[root] = root;
    for (int i = 0; i < n; i++) {
        assert(to_min[i] == i);//because distinct numbers
        assert(-1 <= le[i] && le[i] < i && i < ri[i] && ri[i] <= n);
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
