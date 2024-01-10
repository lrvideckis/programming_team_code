#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"
#include "../template.hpp"
#include "../mono_st_asserts.hpp"

#include "../../../library/monotonic_stack_related/cartesian_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    mono_st_asserts(arr);
    auto [root, adj, le, ri, node] = get_cart_tree(arr, less());
    assert(node[root] == root);
    vector<int> arr_neg(n);
    transform(begin(arr), end(arr), begin(arr_neg), [](int x) {return -x;});
    auto [root_neg, adj_neg, le_neg, ri_neg, node_neg] = get_cart_tree(arr_neg, greater());
    assert(node_neg[root_neg] == root_neg);
    assert(root == root_neg);
    assert(adj == adj_neg);
    assert(le == le_neg);
    assert(ri == ri_neg);
    assert(node == node_neg);
    vector<int> par(n, -1);
    par[root] = root;
    for (int i = 0; i < n; i++) {
        assert(node[i] == i);//because distinct numbers
        assert(-1 <= le[i] && le[i] < i && i < ri[i] && ri[i] <= n);
        assert(le[i] == -1 || arr[le[i]] < arr[i]);
        assert(ri[i] == n || arr[i] > arr[ri[i]]);//because distinct numbers, if dups, then arr[i] >= arr[ri[i]]
        for (int j : adj[i]) {
            assert(le[i] <= le[j] && ri[j] <= ri[i]);
            par[j] = i;
        }
    }
    for (int i = 0; i < n; i++) cout << par[i] << " ";
    return 0;
}
