#pragma once
//library checker tests: https://judge.yosupo.jp/problem/shortest_path
//returns array `len` where `len[i]` = shortest path from node v to node i
//For example len[v] will always = 0
const long long inf = 1e18;
vector<long long> dijkstra(const vector<vector<pair<int, long long>>>& adj /*directed or undirected, weighted graph*/, int v) {
	vector<long long> len(adj.size(), inf);
	len[v] = 0;
	set<pair<long long/*weight*/, int/*node*/>> q;
	q.insert({0LL, v});
	while (!q.empty()) {
		auto it = q.begin();
		int node = it->second;
		q.erase(it);
		for (auto [to, weight] : adj[node])
			if (len[to] > weight + len[node]) {
				q.erase({len[to], to});
				len[to] = weight + len[node];
				q.insert({len[to], to});
			}
	}
	return len;
}
