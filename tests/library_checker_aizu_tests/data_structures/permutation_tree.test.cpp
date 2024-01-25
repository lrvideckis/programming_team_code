#define PROBLEM "https://judge.yosupo.jp/problem/common_interval_decomposition_tree"
#include "../template.hpp"
#include "../perm_tree_asserts.hpp"

#include "../../../library/data_structures/uncommon/permutation_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    perm_tree pt(a);
    perm_tree_asserts(a, pt);
    auto is_join = pt.is_join;
    auto mn_idx = pt.mn_idx;
    auto mn_val = pt.mn_val;
    auto len = pt.len;
    auto root = pt.root;
    auto adj = pt.adj;
    cout << ssize(adj) << '\n';
    int curr_time = 0;
    vector<int> node_to_time(ssize(adj), -1);
    auto dfs = [&](auto&& self, int u, int p) -> void {
        node_to_time[u] = curr_time++;
        cout << (p == -1 ? p : node_to_time[p]) << " " << mn_idx[u] << " " << mn_idx[u] + len[u] - 1 << " " << (is_join[u] || empty(adj[u]) ? "linear" : "prime") << '\n';
        for (int v : adj[u])
            self(self, v, u);
    };
    dfs(dfs, root, -1);
    return 0;
}
