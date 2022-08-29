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
	vector<int> d, ptr;
	max_flow(int n) : g(n), d(n), ptr(n) {}
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
		while (bfs(s, t)) {
			ptr.assign(ptr.size(), 0);
			while (ll pushed = dfs(s, t, INF))
				flow += pushed;
		}
		return flow;
	}
	bool bfs(int s, int t) {
		queue<int> q({s});
		d.assign(d.size(), -1);
		d[s] = 0;
		while (!q.empty() && d[t] == -1) {
			int v = q.front();
			q.pop();
			for (int id : g[v]) {
				int to = e[id].b;
				if (d[to] == -1 && e[id].flow < e[id].cap) {
					q.push(to);
					d[to] = d[v] + 1;
				}
			}
		}
		return d[t] != -1;
	}
	ll dfs(int v, int t, ll flow) {
		if (!flow) return 0;
		if (v == t) return flow;
		for (; ptr[v] < (int)g[v].size(); ptr[v]++) {
			int id = g[v][ptr[v]], to = e[id].b;
			if (d[to] != d[v] + 1) continue;
			if (ll pushed = dfs(to, t, min(flow, e[id].cap - e[id].flow))) {
				e[id].flow += pushed;
				e[id ^ 1].flow -= pushed;
				return pushed;
			}
		}
		return 0;
	}
};
