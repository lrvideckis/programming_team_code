#define PROBLEM "https://judge.yosupo.jp/problem/common_interval_decomposition_tree"
#include "../template.hpp"

#include "../../../library/data_structures/uncommon/permutation_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    perm_tree pt(a);
    cout << ssize(pt.adj) << '\n';
    int curr_time = 0;
    vector<int> node_to_time(ssize(pt.adj), -1);
    auto dfs = [&](auto&& self, int u, int p) -> void {
        node_to_time[u] = curr_time++;
        cout << (p == -1 ? p : node_to_time[p]) << " " << pt.mn_idx[u] << " " << pt.mn_idx[u] + pt.len[u] - 1 << " " << (pt.is_join[u] ? "linear" : "prime") << '\n';
        for (int v : pt.adj[u])
            self(self, v, u);
    };
    dfs(dfs, pt.root, -1);
    return 0;
}
