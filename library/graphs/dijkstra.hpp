/** @file */
#pragma once
/**
 * @param adj directed or undirected, weighted graph
 * @param start a node
 * @returns array `len` where `len[i]` = shortest path from node `start` to node
 * `i`. `len[start]` is always 0.
 * @time O((n + m) log n) Note log(m) < log(n^2) = 2*log(n), so O(log n) ==
 * O(log m)
 * @memory O(n + m)
 */
vector<long long> dijkstra(const vector<vector<pair<int, long long>>>& adj, int start) {
	using node = pair<long long, int>;
	vector<long long> len(ssize(adj), LLONG_MAX);
	len[start] = 0;
	priority_queue<node, vector<node>, greater<node>> q;
	q.emplace(0, start);
	while (!q.empty()) {
		auto [curr_len, u] = q.top();
		q.pop();
		if (len[u] < curr_len) continue;//important check: O(n*m) without it
		for (auto [v, weight] : adj[u])
			if (len[v] > weight + len[u]) {
				len[v] = weight + len[u];
				q.emplace(len[v], v);
			}
	}
	return len;
}
