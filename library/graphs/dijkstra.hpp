#pragma once
const long long INF = 1e18;
/**
 * @brief Returns array `len` where `len[i]` = shortest path from node `start`
 *     to node `i`. For example `len[start]` will always = 0.
 * @time O((n + m) log n) - note log(m) < log(n^2) = 2*log(n), so
 *     O(log n) == O(log m)
 * @memory O(n + m)
 */
vector<long long> dijkstra(const vector<vector<pair<int, long long>>>& adj /*directed or undirected, weighted graph*/, int start) {
	using node = pair<long long, int>;
	vector<long long> len(ssize(adj), INF);
	len[start] = 0;
	priority_queue<node, vector<node>, greater<node>> q;
	q.emplace(0, start);
	while (!q.empty()) {
		auto [curr_len, v] = q.top();
		q.pop();
		if (len[v] < curr_len)
			continue;//important check: O(n*m) without it
		for (auto [to, weight] : adj[v])
			if (len[to] > weight + len[v]) {
				len[to] = weight + len[v];
				q.emplace(len[to], to);
			}
	}
	return len;
}
