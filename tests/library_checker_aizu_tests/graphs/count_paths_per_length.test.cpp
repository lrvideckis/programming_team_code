#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"
#include "../../../library/graphs/centroid_decomp/count_paths_per_node.hpp"

#include "../../../library/graphs/centroid_decomp/count_paths_per_length.hpp"

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
        //check each node is the centroid of exactly one decomposition
        vector<bool> seen_cent(n);
        centroid(adj, [&](const vector<vector<int>>& adj_cd, int cent) -> void {
            assert(!seen_cent[cent]);
            seen_cent[cent] = 1;
            auto dfs = [&](auto&& self, int u, int p) -> int {
                int sub_size = 1;
                for (int v : adj_cd[u])
                    if (v != p)
                        sub_size += self(self, v, u);
                return sub_size;
            };
            int sz_decomp = dfs(dfs, cent, -1);
            int sum = 1;
            for (int u : adj_cd[cent]) {
                int sz_subtree = dfs(dfs, u, cent);
                sum += sz_subtree;
                assert(1 <= sz_subtree && 2 * sz_subtree <= sz_decomp);
            }
            assert(sum == sz_decomp);
        });
        assert(find(begin(seen_cent), end(seen_cent), 0) == end(seen_cent));
    }
    vector<long long> cnt_len = count_paths_per_length(adj);
    if (n >= 2) {
        int k = get_rand(1, n - 1);
        vector<long long> count_paths = count_paths_per_node(adj, k);
        long long sum = accumulate(begin(count_paths), end(count_paths), 0LL);
        assert(sum % (k + 1) == 0);
        assert(sum / (k + 1) == cnt_len[k]);
    }
    for (int i = 1; i < n; i++)
        cout << cnt_len[i] << " ";
    cout << '\n';
    return 0;
}
