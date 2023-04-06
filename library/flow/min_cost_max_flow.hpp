/** @file */
#pragma once
/**
 * @see https://e-maxx.ru/algo/min_cost_flow
 */
struct mcmf {
	using ll = long long;
	struct edge {
		int u, v;
		ll cap, cost, flow;
		int back;
	};
	const int N;
	vector<edge> e; /**< edge list */
	vector<vector<int>> adj; /**< adjacency list */
	/**
	 * @param a_n number of nodes. Note 0 <= s,t < a_n
	 */
	mcmf(int a_n) : N(a_n), adj(N) {}
	void add_edge(int u, int v, ll cap, ll cost) {
		edge e1 = {u, v, cap, cost, 0, ssize(adj[v])};
		edge e2 = {v, u, 0, -cost, 0, ssize(adj[u])};
		adj[u].push_back(ssize(e));
		e.push_back(e1);
		adj[v].push_back(ssize(e));
		e.push_back(e2);
	}
	/**
	 * @param s source
	 * @param t sink
	 * @param total_flow we try to send this amount of flow through the graph
	 * @returns pair(flow, cost)
	 * - flow: (<=total_flow) is the max amount of flow we are able to send.
	 * - cost: minimum sum of: (edge.flow * edge.cost) over each edge (over all
	 *   ways to send `flow` flow)
	 */
	pair<ll, ll> get_flow(int s, int t, ll total_flow) {
		ll flow = 0, cost = 0;
		while (flow < total_flow) {
			vector<ll> d(N, LLONG_MAX);
			vector<int> p_edge(N), id(N), q(N), p(N);
			int qh = 0, qt = 0;
			q[qt++] = s;
			d[s] = 0;
			while (qh != qt) {
				int u = q[qh++];
				id[u] = 2;
				if (qh == N) qh = 0;
				for (int i = 0; i < ssize(adj[u]); i++) {
					const edge& r = e[adj[u][i]];
					if (r.flow < r.cap && d[u] + r.cost < d[r.v]) {
						d[r.v] = d[u] + r.cost;
						if (id[r.v] == 0) {
							q[qt++] = r.v;
							if (qt == N) qt = 0;
						} else if (id[r.v] == 2) {
							if (--qh == -1) qh = N - 1;
							q[qh] = r.v;
						}
						id[r.v] = 1;
						p[r.v] = u;
						p_edge[r.v] = i;
					}
				}
			}
			if (d[t] == LLONG_MAX) break;
			ll addflow = total_flow - flow;
			for (int u = t; u != s; u = p[u]) {
				int pv = p[u], pr = p_edge[u];
				addflow = min(addflow, e[adj[pv][pr]].cap - e[adj[pv][pr]].flow);
			}
			for (int u = t; u != s; u = p[u]) {
				int pv = p[u], pr = p_edge[u], r = e[adj[pv][pr]].back;
				e[adj[pv][pr]].flow += addflow;
				e[adj[u][r]].flow -= addflow;
				cost += e[adj[pv][pr]].cost * addflow;
			}
			flow += addflow;
		}
		return {flow, cost};
	}
};
