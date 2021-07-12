struct mincostmaxflow {
	struct edge {
	 int a, b, cap, cost, flow;
		size_t back;
	};

	vector<edge> e;
	vector<vector<ll>> g;
 int n, s, t;
 int k = inf; // The maximum amount of flow allowed

	mincostmaxflow(int _n, int _s, int _t) : n(_n), s(_s), t(_t) {
		g.resize(n);
	}

	void addedge(int a, int b, int cap, int cost) {
		edge e1 = {a,b,cap,cost,0,g[b].size()};
		edge e2 = {b,a,0,-cost,0,g[a].size()};
		g[a].push_back((ll) e.size());
		e.push_back(e1);
		g[b].push_back((ll) e.size());
		e.push_back(e2);
	}

	// Returns {flow,cost}
	pair<ll,ll> getflow() {
	 int flow = 0, cost = 0;
		while(flow < k) {
			vector<ll> id(n, 0);
			vector<ll> d(n, inf);
			vector<ll> q(n);
			vector<ll> p(n);
			vector<size_t> p_edge(n);
		 int qh=0, qt=0;
			q[qt++] = s;
			d[s] = 0;
			while(qh != qt) {
			 int v = q[qh++];
				id[v] = 2;
				if(qh == n) qh = 0;
				for(size_t i=0; i<g[v].size(); ++i) {
					edge& r = e[g[v][i]];
					if(r.flow < r.cap && d[v] + r.cost < d[r.b]) {
						d[r.b] = d[v] + r.cost;
						if(id[r.b] == 0) {
							q[qt++] = r.b;
							if(qt == n) qt = 0;
						}
						else if(id[r.b] == 2) {
							if(--qh == -1) qh = n-1;
							q[qh] = r.b;
						}
						id[r.b] = 1;
						p[r.b] = v;
						p_edge[r.b] = i;
					}
				}
			}
			if(d[t] == inf) break;
		 int addflow = k - flow;
			for(int v=t; v!=s; v=p[v]) {
			 int pv = p[v]; size_t pr = p_edge[v];
				addflow = min(addflow, e[g[pv][pr]].cap - e[g[pv][pr]].flow);
			}
			for(int v=t; v!=s; v=p[v]) {
			 int pv = p[v]; size_t pr = p_edge[v], r = e[g[pv][pr]].back;
				e[g[pv][pr]].flow += addflow;
				e[g[v][r]].flow -= addflow;
				cost += e[g[pv][pr]].cost * addflow;
			}
			flow += addflow;
		}
		return {flow,cost};
	}
};
