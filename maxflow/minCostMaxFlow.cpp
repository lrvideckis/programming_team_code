#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;

const ll MAXN = 1e5+10;
const ll INF = (ll)1e9;

struct edge {
    ll b, u, c, f;
    size_t back;
};

int n, k = INF, s, t;
vector<edge> g[MAXN];

void reset() {
    for(int i = 0; i < n; ++i) {
        g[i].clear();
    }
}

void addedge(int a, int b, int cap, int cost) {
    edge r1 = {b, cap, cost, 0, g[b].size()};
    edge r2 = {a, 0, -cost, 0, g[a].size()};
    g[a].push_back(r1);
    g[b].push_back(r2);
}

pair<ll, ll> flow() {//max flow, min cut
    int flow = 0, cost = 0;
    while(flow < k) {
        vector<int> id(n,0);
        vector<int> d(n, INF);
        vector<int> q(n);
        vector<int> p(n);
        vector<size_t> p_edge(n);
        int qh = 0, qt = 0;
        q[qt++] = s;
        d[s] = 0;
        while(qh != qt) {
            int v = q[qh++];
            id[v] = 2;
            if(qh == n) qh = 0;
            for(size_t i = 0; i < g[v].size(); ++i) {
                edge &r = g[v][i];
                if(r.f < r.u && d[v] + r.c < d[r.b]) {
                    d[r.b] = d[v] + r.c;
                    if(id[r.b] == 0) {
                        q[qt++] = r.b;
                        if(qt == n) qt = 0;
                    } else if(id[r.b] == 2) {
                        if(--qh == -1) qh = n-1;
                        q[qh] = r.b;
                    }
                    id[r.b] = 1;
                    p[r.b] = v;
                    p_edge[r.b] = i;
                }
            }
        }
        if(d[t] == INF) break;
        int addflow = k-flow;
        for(int v = t; v != s; v = p[v]) {
            int pv = p[v]; size_t pr = p_edge[v];
            addflow = min(addflow, g[pv][pr].u - g[pv][pr].f);
        }
        for(int v = t; v != s; v = p[v]) {
            int pv = p[v]; size_t pr = p_edge[v], r = g[pv][pr].back;
            g[pv][pr].f += addflow;
            g[v][r].f -= addflow;
            cost += g[pv][pr].c * addflow;
        }
        flow += addflow;
    }
    return {flow, cost};
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int m;
    cin >> n >> m >> s >> t;
    for(int i = 0; i < m; ++i) {
        int u, v, c, w;
        cin >> u >> v >> c >> w;
        addedge(u, v, c, w);
    }
    pair<ll, ll> res = flow();
    cout << res.first << ' ' << res.second << '\n';
    return 0;
}



