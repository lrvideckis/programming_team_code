#pragma once
//status: not tested
struct max_flow {
	typedef long long ll;
	ll n, s, t;
	max_flow(int a_n, int a_s, int a_t) : n(a_n), s(a_s), t(a_t), d(n), ptr(n), q(n), g(n) {}
	void add_edge(ll a, ll b, ll cap) {
		edge_map[a * n + b] = ssize(e);
		edge e1 = { a, b, cap, 0 };
		edge e2 = { b, a, 0, 0 };
		g[a].push_back((ll) ssize(e));
		e.push_back(e1);
		g[b].push_back((ll) ssize(e));
		e.push_back(e2);
	}
	ll get_flow() {
		ll flow = 0;
		for (;;) {
			if (!bfs()) break;
			ptr.assign(ssize(ptr), 0);
			while (ll pushed = dfs(s, INF))
				flow += pushed;
		}
		return flow;
	}
	ll get_flow_for_edge(ll a, ll b) {
		return e[edge_map[a * n + b]].flow;
	}
	const ll INF = 1e18;
	struct edge {
		ll a, b, cap, flow;
	};
	unordered_map<int, ll> edge_map;
	vector<ll> d, ptr, q;
	vector<edge> e;
	vector<vector<ll>> g;
	bool bfs() {
		ll qh = 0, qt = 0;
		q[qt++] = s;
		d.assign(ssize(d), -1);
		d[s] = 0;
		while (qh < qt && d[t] == -1) {
			ll v = q[qh++];
			for (int i = 0; i < ssize(g[v]); i++) {
				ll id = g[v][i],
				   to = e[id].b;
				if (d[to] == -1 && e[id].flow < e[id].cap) {
					q[qt++] = to;
					d[to] = d[v] + 1;
				}
			}
		}
		return d[t] != -1;
	}
	ll dfs(ll v, ll flow) {
		if (!flow) return 0;
		if (v == t) return flow;
		for (; ptr[v] < (ll) ssize(g[v]); ptr[v]++) {
			ll id = g[v][ptr[v]];
			ll to = e[id].b;
			if (d[to] != d[v] + 1) continue;
			ll pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
			if (pushed) {
				e[id].flow += pushed;
				e[id ^ 1].flow -= pushed;
				return pushed;
			}
		}
		return 0;
	}
};
