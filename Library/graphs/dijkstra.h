#pragma once

//returns array `len` where `len[i]` = shortest path from node `startNode` to node i
//For example len[startNode] will always = 0
//
//status: tested on https://judge.yosupo.jp/problem/shortest_path

const long long INF = 1e18;

vector<long long> dijkstra(const vector<vector<pair<int, long long>>>& adj /*directed or undirected, weighted graph*/, int startNode) {
	vector<long long> len(adj.size(), INF);
	len[startNode] = 0;
	set<pair<long long/*weight*/, int/*node*/>> q;
	q.insert({0LL, startNode});
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
