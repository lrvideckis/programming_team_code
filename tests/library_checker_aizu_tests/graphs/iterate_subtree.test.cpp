#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "../template.hpp"

#include "../../../library/graphs/lca_rmq/get_lca.hpp"
#include "../../../library/graphs/lca_rmq/iterate_subtree.hpp"
#include "../../../library/graphs/lca_rmq/in_subtree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int par;
        cin >> par;
        adj[par].push_back(i);
    }
    LCA lca(adj);
    {
        vector<int> cnt_small_iterated(n), cnt_big_iterated(n);
        for (int i = 0; i < n; i++) {
            if(adj[i].empty()) continue;
            int big_ch_idx = int(max_element(begin(adj[i]), end(adj[i]), [&](int x, int y) {return lca.sub_sz[x] < lca.sub_sz[y];}) - begin(adj[i]));
            for (int j = 0; j < ssize(adj[i]); j++) {
                assert(lca.sub_sz[adj[i][j]] <= lca.sub_sz[adj[i][big_ch_idx]]);
                int u = adj[i][j];
                if(j == big_ch_idx) {
                    int le = lca.in[u];
                    int ri = lca.in[u] + lca.sub_sz[u];
                    cnt_big_iterated[le]++;
                    if(ri < n) cnt_big_iterated[ri]--;
                    continue;
                }
                iterate_subtree(lca, u, [&](int v) {
                    assert(lca.d[u] <= lca.d[v]);
                    assert(in_subtree(lca, u, v));
                    cnt_small_iterated[v]++;
                });
            }
        }
        partial_sum(begin(cnt_big_iterated), end(cnt_big_iterated), begin(cnt_big_iterated));
        for (int i = 0; i < n; i++) {
            //at each merge (small to large), subtree size doubles or more
            //how many doubles until it reaches n?
            //sub_sz * 2^k ~= n
            //2^k ~= n / sub_sz
            //k ~= __lg(n / sub_sz)
            assert(cnt_small_iterated[i] <= __lg(n / lca.sub_sz[i]));
            assert(cnt_small_iterated[i] + cnt_big_iterated[lca.in[i]] == lca.d[i]);
        }
    }
    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << get_lca(lca, u, v) << '\n';
    }
}
