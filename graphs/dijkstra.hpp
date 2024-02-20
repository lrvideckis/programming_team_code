/**
 * @param adj directed or undirected, weighted graph
 * @param s a node
 * @returns array `d` where `d[i]` = shortest path from node `s` to node
 * `i`. `d[s]` is always 0.
 * @time O((n + m) log n) Note log(m) < log(n^2) = 2*log(n), so O(log n) ==
 * O(log m)
 * @space besides the O(n + m) param `adj`, this function allocates/returns a
 * O(n) distance array. The (temporary) priority queue can grow to size O(n+m)
 */
vector<int64_t> dijkstra(const vector<vector<pair<int, int64_t>>>& adj, int s) {
	using node = pair<int64_t, int>;
	vector<int64_t> d(ssize(adj), LLONG_MAX);
	d[s] = 0;
	priority_queue<node, vector<node>, greater<node>> pq;
	pq.emplace(0, s);
	while (!empty(pq)) {
		auto [d_u, u] = pq.top();
		pq.pop();
		if (d[u] < d_u) continue;//important check: O(n*m) without it
		for (auto [v, w] : adj[u])
			if (d[v] > w + d[u]) {
				d[v] = w + d[u];
				pq.emplace(d[v], v);
			}
	}
	return d;
}
