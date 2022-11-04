#pragma once
const long long INF = 1e18;
/**
 * @see https://e-maxx.ru/algo/min_cost_flow
 */
struct mcmf {
	using ll = long long;
	struct edge {
		int a, b;
		ll cap, cost, flow;
		int back;
	};
	const int N;
	vector<edge> e;
	vector<vector<int>> g;
	mcmf(int a_n) : N(a_n), g(N) {}
	void add_edge(int a, int b, ll cap, ll cost) {
		edge e1 = {a, b, cap, cost, 0, ssize(g[b])};
		edge e2 = {b, a, 0, -cost, 0, ssize(g[a])};
		g[a].push_back(ssize(e));
		e.push_back(e1);
		g[b].push_back(ssize(e));
		e.push_back(e2);
	}
	pair<ll, ll> get_flow(int s, int t, ll total_flow) {
		ll flow = 0, cost = 0;
		while (flow < total_flow) {
			vector<ll> d(N, INF);
			vector<int> p_edge(N), id(N, 0), q(N), p(N);
			int qh = 0, qt = 0;
			q[qt++] = s;
			d[s] = 0;
			while (qh != qt) {
				int v = q[qh++];
				id[v] = 2;
				if (qh == N) qh = 0;
				for (int i = 0; i < ssize(g[v]); i++) {
					const edge& r = e[g[v][i]];
					if (r.flow < r.cap && d[v] + r.cost < d[r.b]) {
						d[r.b] = d[v] + r.cost;
						if (id[r.b] == 0) {
							q[qt++] = r.b;
							if (qt == N) qt = 0;
						} else if (id[r.b] == 2) {
							if (--qh == -1) qh = N - 1;
							q[qh] = r.b;
						}
						id[r.b] = 1;
						p[r.b] = v;
						p_edge[r.b] = i;
					}
				}
			}
			if (d[t] == INF) break;
			ll addflow = total_flow - flow;
			for (int v = t; v != s; v = p[v]) {
				int pv = p[v], pr = p_edge[v];
				addflow = min(addflow, e[g[pv][pr]].cap - e[g[pv][pr]].flow);
			}
			for (int v = t; v != s; v = p[v]) {
				int pv = p[v], pr = p_edge[v], r = e[g[pv][pr]].back;
				e[g[pv][pr]].flow += addflow;
				e[g[v][r]].flow -= addflow;
				cost += e[g[pv][pr]].cost * addflow;
			}
			flow += addflow;
		}
		return {flow, cost};
	}
};
