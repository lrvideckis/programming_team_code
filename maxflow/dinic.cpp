#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;

const ll MAXN = 1e6+10;
const ll INF = (ll)1e9;

struct edge {
	ll a, b, cap, flow;
};

ll n, s, t, d[MAXN], ptr[MAXN], q[MAXN];
vector<edge> e;
vector<ll> g[MAXN];

void reset() {
    e.clear();
    for(int i = 0; i < n; ++i) {
        g[i].clear();
    }
}

void addedge(ll a, ll b, ll cap) {
	edge e1 = { a, b, cap, 0 };
	edge e2 = { b, a, 0, 0 };
	g[a].push_back((ll) e.size());
	e.push_back(e1);
	g[b].push_back((ll) e.size());
	e.push_back(e2);
}

bool bfs() {
	ll qh=0, qt=0;
	q[qt++] = s;
	memset(d, -1, n * sizeof d[0]);
	d[s] = 0;
	while(qh < qt && d[t] == -1) {
		ll v = q[qh++];
		for(size_t i=0; i<g[v].size(); ++i) {
			ll id = g[v][i],
				to = e[id].b;
			if(d[to] == -1 && e[id].flow < e[id].cap) {
				q[qt++] = to;
				d[to] = d[v] + 1;
			}
		}
	}
	return d[t] != -1;
}

ll dfs(ll v, ll flow) {
	if(!flow)  return 0;
	if(v == t)  return flow;
	for(; ptr[v]<(ll)g[v].size(); ++ptr[v]) {
		ll id = g[v][ptr[v]];
        ll to = e[id].b;
		if(d[to] != d[v] + 1)  continue;
		ll pushed = dfs(to, min (flow, e[id].cap - e[id].flow));
		if(pushed) {
			e[id].flow += pushed;
			e[id^1].flow -= pushed;
			return pushed;
		}
	}
	return 0;
}

ll dinic() {//O(min(V^2*E, V*E^2, E*flow))
	ll flow = 0;
	for(;;) {
		if(!bfs())  break;
		memset(ptr, 0, n * sizeof ptr[0]);
		while(ll pushed = dfs(s,INF)) {
			flow += pushed;
        }
	}
	return flow;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int m;
    cin >> n >> m >> s >> t;
    int u, v, c;
    for(int i = 0; i < m; ++i) {
        cin >> u >> v >> c;
        addedge(u,v,c);
    }
    int flow = dinic();
    vector<pair<int, pair<int, int>>> edgesUsed;
    for(auto &currEdge : e) {
        if(currEdge.flow > 0) {
            edgesUsed.push_back({currEdge.a, {currEdge.b, currEdge.flow}});
        }
    }
    cout << n << ' ' << flow << ' ' << edgesUsed.size() << '\n';
    for(auto &p : edgesUsed) {
        cout << p.first << ' ' << p.second.first << ' ' << p.second.second << '\n';
    }
    return 0;
}



























