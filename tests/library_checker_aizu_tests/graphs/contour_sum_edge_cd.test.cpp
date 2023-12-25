#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_range_contour_sum_on_tree"
#include "../template.hpp"

#include "../../../library/graphs/edge_centroid_decomp/contour_sum.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
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
    contour_sum<long long> cs(adj, a);
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int u;
            long long delta;
            cin >> u >> delta;
            cs.update(u, delta);
        } else {
            assert(type == 1);
            int u, le, ri;
            cin >> u >> le >> ri;
            cout << cs.query(u, le, ri) << '\n';
        }
    }
    return 0;
}
