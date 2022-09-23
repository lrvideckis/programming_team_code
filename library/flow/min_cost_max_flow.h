#pragma once
//status: not tested
const long long INF = 1e18;
struct min_cost_max_flow {
	typedef long long ll;
	struct edge {
		ll a, b, cap, cost, flow;
		int back;
	};
	vector<edge> e;
	vector<vector<ll>> g;
	ll n, s, t;
	ll k = INF; // max amount of flow allowed
	min_cost_max_flow(int a_n, int a_s, int a_t) : n(a_n), s(a_s), t(a_t) {
		g.resize(n);
	}
	void add_edge(ll a, ll b, ll cap, ll cost) {
		edge e1 = {a, b, cap, cost, 0, (int)ssize(g[b]) };
		edge e2 = {b, a, 0, -cost, 0, (int)ssize(g[a]) };
		g[a].push_back(ssize(e));
		e.push_back(e1);
		g[b].push_back(ssize(e));
		e.push_back(e2);
	}
	// returns {flow, cost}
	pair<ll, ll> get_flow() {
		ll flow = 0, cost = 0;
		while (flow < k) {
			vector<ll> id(n, 0), d(n, INF), q(n), p(n);
			vector<int> p_edge(n);
			ll qh = 0, qt = 0;
			q[qt++] = s;
			d[s] = 0;
			while (qh != qt) {
				ll v = q[qh++];
				id[v] = 2;
				if (qh == n) qh = 0;
				for (int i = 0; i < ssize(g[v]); i++) {
					edge& r = e[g[v][i]];
					if (r.flow < r.cap && d[v] + r.cost < d[r.b]) {
						d[r.b] = d[v] + r.cost;
						if (id[r.b] == 0) {
							q[qt++] = r.b;
							if (qt == n) qt = 0;
						} else if (id[r.b] == 2) {
							if (--qh == -1) qh = n - 1;
							q[qh] = r.b;
						}
						id[r.b] = 1;
						p[r.b] = v;
						p_edge[r.b] = i;
					}
				}
			}
			if (d[t] == INF) break;
			ll addflow = k - flow;
			for (ll v = t; v != s; v = p[v]) {
				ll pv = p[v];
				int pr = p_edge[v];
				addflow = min(addflow, e[g[pv][pr]].cap - e[g[pv][pr]].flow);
			}
			for (ll v = t; v != s; v = p[v]) {
				ll pv = p[v];
				int pr = p_edge[v], r = e[g[pv][pr]].back;
				e[g[pv][pr]].flow += addflow;
				e[g[v][r]].flow -= addflow;
				cost += e[g[pv][pr]].cost * addflow;
			}
			flow += addflow;
		}
		return {flow, cost};
	}
};
