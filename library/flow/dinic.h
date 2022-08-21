#pragma once
struct max_flow {
	using ll = long long;
	const ll INF = 1e18;
	struct edge {
		int a, b;
		ll cap, flow;
	};
	vector<edge> e;
	vector<vector<int>> g;
	vector<int> q, d, ptr;
	max_flow(int n) : g(n), q(n), d(n), ptr(n) {}
	void add_edge(int a, int b, ll cap) {
		edge e1 = { a, b, cap, 0 };
		edge e2 = { b, a, 0, 0 };
		g[a].push_back(e.size());
		e.push_back(e1);
		g[b].push_back(e.size());
		e.push_back(e2);
	}
	ll get_flow(int s, int t) {
		ll flow = 0;
		for (;;) {
			if (!bfs(s, t)) break;
			ptr.assign(ptr.size(), 0);
			while (ll pushed = dfs(s, INF, t))
				flow += pushed;
		}
		return flow;
	}
	bool bfs(int s, int t) {
		int qh = 0, qt = 0;
		q[qt++] = s;
		d.assign(d.size(), -1);
		d[s] = 0;
		while (qh < qt && d[t] == -1) {
			int v = q[qh++];
			for (int i = 0; i < (int)g[v].size(); i++) {
				int id = g[v][i], to = e[id].b;
				if (d[to] == -1 && e[id].flow < e[id].cap) {
					q[qt++] = to;
					d[to] = d[v] + 1;
				}
			}
		}
		return d[t] != -1;
	}
	ll dfs(int v, ll flow, int t) {
		if (!flow) return 0;
		if (v == t) return flow;
		for (; ptr[v] < (int)g[v].size(); ptr[v]++) {
			int id = g[v][ptr[v]], to = e[id].b;
			if (d[to] != d[v] + 1) continue;
			ll pushed = dfs(to, min(flow, e[id].cap - e[id].flow), t);
			if (pushed) {
				e[id].flow += pushed;
				e[id ^ 1].flow -= pushed;
				return pushed;
			}
		}
		return 0;
	}
};
