#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"
#include "../template.hpp"

#include "../../../library/graphs/edge_centroid_decomp/count_paths_per_length.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    {
        edge_cd(adj, [&](const vector<vector<int>>& cd_adj, int cent, int split) -> void {
            auto dfs = [&](auto&& self, int u, int p) -> int {
                int siz = 1;
                for (int v : cd_adj[u])
                    if (v != p) siz += self(self, v, u);
                return siz;
            };
            int sz_all = dfs(dfs, cent, -1);
            array<int, 2> cnts = {0, 0};
            for (int i = 0; i < ssize(cd_adj[cent]); i++) {
                int sz_subtree = dfs(dfs, cd_adj[cent][i], cent);
                assert(2 * sz_subtree <= sz_all);
                cnts[i < split] += sz_subtree;
            }
            assert(cnts[0] + cnts[1] + 1 == sz_all);
            for (int i = 0; i < 2; i++)
                assert(cnts[i] <= 2 * cnts[!i]);
        });
    }
    vector<long long> cnt_len = count_paths_per_length(adj);
    for (int i = 1; i < n; i++)
        cout << cnt_len[i] << " ";
    cout << '\n';
    return 0;
}
