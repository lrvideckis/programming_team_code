#pragma once

//returns array `len` where `len[i]` = shortest path from node `startNode` to node i
//For example len[startNode] will always = 0
//
//status: tested on random graphs against floyd warshals, and on https://judge.yosupo.jp/problem/shortest_path

const long long INF = 1e18;

struct dij {
	vector<long long> len;
	vector<int> par;
};

dij dijkstra(const vector<vector<pair<int, long long>>>& adj /*directed or undirected, weighted graph*/, int startNode) {
	vector<long long> len(adj.size(), INF);
	vector<int> par(adj.size(), -1);
	len[startNode] = 0;
	set<pair<long long, int>> q;//weight, node
	q.insert({0, startNode});
	while (!q.empty()) {
		auto it = q.begin();
		const int node = it->second;
		q.erase(it);
		for (auto [to, weight] : adj[node]) {
			if (len[to] > weight + len[node]) {
				q.erase({len[to], to});
				len[to] = weight + len[node];
				par[to] = node;
				q.insert({len[to], to});
			}
		}
	}
	return dij{len, par};
}
