#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include "../template.hpp"

#include "../../../library/graphs/tree_lift/kth_path.hpp"
#include "../../../library/graphs/tree_lift/dist_edges.hpp"

#include "../../../library/graphs/centroid_decomp/centroid_decomp.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n + n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        adj[u + n].push_back(v + n);
        adj[v + n].push_back(u + n);
    }
    // for each node u:
    // - decomp_info[u] is a vector of length O(log n)
    // - decomp_info[u][depth] = {distance from node u to the centroid, centroid}
    //       in the decomposition which is depth `depth` in the centroid tree
    vector<vector<array<int, 2>>> decomp_info(n + n);
    vector<bool> seen_cent(n + n);
    centroid(adj, [&](const vector<vector<int>>& adj_removed_edges, int cent) -> void {
        assert(!seen_cent[cent]);
        seen_cent[cent] = 1;
        auto dfs = [&](auto&& self, int u, int p, int dist) -> void {
            decomp_info[u].push_back({dist, cent});
            for (int v : adj_removed_edges[u])
                if (v != p)
                    self(self, v, u, 1 + dist);
        };
        dfs(dfs, cent, -1, 0);
    });
    assert(find(begin(seen_cent), end(seen_cent), 0) == end(seen_cent));
    auto path_dist_via_cd = [&](int u, int v) -> int {
        int dep = int(min(ssize(decomp_info[u]), ssize(decomp_info[v]))) - 1;
        while (dep >= 0 && decomp_info[u][dep][1] != decomp_info[v][dep][1]) dep--;
        if (dep < 0) return dep;
        return decomp_info[u][dep][0] + decomp_info[v][dep][0];
    };
    tree_lift tl(adj);
    while (q--) {
        int u, v, k;
        cin >> u >> v >> k;
        int dist_in_edges = dist_edges(tl, u, v);
        if (k > dist_in_edges)
            cout << -1 << '\n';
        else
            cout << kth_path(tl, u, v, k) << '\n';
        assert(path_dist_via_cd(u, v) == dist_in_edges);
        assert(path_dist_via_cd(v + n, u + n) == dist_in_edges);
        assert(path_dist_via_cd(u, v + n) == -1);
        assert(path_dist_via_cd(u + n, v) == -1);
    }
}
