#define PROBLEM "https://judge.yosupo.jp/problem/common_interval_decomposition_tree"
#include "../template.hpp"

#include "../../../library/data_structures/rmq.hpp"
#include "../../../library/data_structures/uncommon/permutation_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    RMQ rmq_min(a, [](int x, int y) {return min(x, y);});
    RMQ rmq_max(a, [](int x, int y) {return max(x, y);});
    perm_tree pt(a);
    auto is_join = pt.is_join;
    auto mn_idx = pt.mn_idx;
    auto mn_val = pt.mn_val;
    auto len = pt.len;
    auto root = pt.root;
    auto adj = pt.adj;
    assert(mn_idx[root] == 0 && mn_val[root] == 0 && len[root] == n);
    cout << ssize(adj) << '\n';
    int curr_time = 0;
    vector<int> node_to_time(ssize(adj), -1);
    auto dfs = [&](auto&& self, int u, int p) -> void {
        {
            int mn_val_rmq = rmq_min.query(mn_idx[u], mn_idx[u] + len[u]);
            assert(mn_val_rmq == mn_val[u]);
            int mx_val_rmq = rmq_max.query(mn_idx[u], mn_idx[u] + len[u]);
            assert(mx_val_rmq - mn_val_rmq + 1 == len[u]);
        }
        if (empty(adj[u])) {
            assert(len[u] == 1);
            assert(u == mn_idx[u]);
            assert(a[u] == mn_val[u]);
            assert(is_join[u]);
        } else {
            assert(len[u] > 1);
            assert(ssize(adj[u]) >= 2);
            assert(mn_idx[u] == mn_idx[adj[u][0]]);
            assert(mn_idx[u] + len[u] == mn_idx[adj[u].back()] + len[adj[u].back()]);
            assert(is_join[u] == (mn_val[u] == mn_val[adj[u][0]] || mn_val[u] == mn_val[adj[u].back()]));
            assert(is_join[u] == (mn_val[u] + len[u] == mn_val[adj[u][0]] + len[adj[u][0]] ||
                                  mn_val[u] + len[u] == mn_val[adj[u].back()] + len[adj[u].back()]));
            for (int i = 1; i < ssize(adj[u]); i++) {
                int prev = adj[u][i - 1], curr = adj[u][i];
                assert(mn_idx[prev] + len[prev] == mn_idx[curr]);
                bool curr_touches = pt.touches(prev, curr);
                assert(is_join[u] == curr_touches);
            }
            int mn_val_naive = n, mx_val_naive = -1, sum_len_naive = 0;
            for (int v : adj[u]) {
                mn_val_naive = min(mn_val_naive, mn_val[v]);
                mx_val_naive = max(mx_val_naive, mn_val[v] + len[v]);
                sum_len_naive += len[v];
            }
            assert(mn_val_naive == mn_val[u]);
            assert(mx_val_naive == mn_val[u] + len[u]);
            assert(sum_len_naive == len[u]);
        }
        node_to_time[u] = curr_time++;
        cout << (p == -1 ? p : node_to_time[p]) << " " << mn_idx[u] << " " << mn_idx[u] + len[u] - 1 << " " << (is_join[u] ? "linear" : "prime") << '\n';
        for (int v : adj[u])
            self(self, v, u);
    };
    dfs(dfs, root, -1);
    return 0;
}
