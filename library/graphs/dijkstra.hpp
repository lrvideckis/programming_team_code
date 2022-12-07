/** @file */
#pragma once
const long long INF = 1e18;
/**
 * @param adj directed or undirected, weighted graph
 * @param u source node
 * @returns array `len` where `len[i]` = shortest path from node `u` to node
 * `i`. `len[u]` is always 0.
 * @time O((n + m) log n) Note log(m) < log(n^2) = 2*log(n), so O(log n) ==
 * O(log m)
 * @memory O(n + m)
 */
vector<long long> dijkstra(const vector<vector<pair<int, long long>>>& adj, int u) {
	using node = pair<long long, int>;
	vector<long long> len(ssize(adj), INF);
	len[u] = 0;
	priority_queue<node, vector<node>, greater<node>> q;
	q.emplace(0, u);
	while (!q.empty()) {
		auto [curr_len, v] = q.top();
		q.pop();
		if (len[v] < curr_len) continue;//important check: O(n*m) without it
		for (auto [to, weight] : adj[v])
			if (len[to] > weight + len[v]) {
				len[to] = weight + len[v];
				q.emplace(len[to], to);
			}
	}
	return len;
}
