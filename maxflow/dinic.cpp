#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll inf = (ll)1 << 60;
const ll MAXN = 100000 + 10;

struct edge {
	ll a, b, cap, flow;
};

ll n, s, t, d[MAXN], ptr[MAXN], q[MAXN];
vector<edge> e;
vector<ll> g[MAXN];

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
	if(!flow) return 0;
	if(v == t) return flow;
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

ll getflow() {
	ll flow = 0;
	for(;;) {
		if(!bfs())  break;
		memset(ptr, 0, n * sizeof ptr[0]);
		while(ll pushed = dfs(s,inf)) {
			flow += pushed;
        }
	}
	return flow;
}

// This requres 'n' to be set to
// its value from the previous run
// This removes all edges from the graph
void reset() {
    e.clear();
    for(int i = 0; i < n; i++) {
        g[i].clear();
    }
}

int main() {
    // You need to set the global number of nodes up front
    n = 3;

    // You need to set the global source and sink up front
    s = 0;
    t = 2;

    // Add an edge from source to node 1 with weight 7
    addedge(s,1,7);

    // Add an edge from node 1 to sink with weight 4
    addedge(1,t,4);

    // Calculate max flow from s to t
    // Dinic's runs in E * V^2
    cout << getflow() << endl;

    reset();
}
