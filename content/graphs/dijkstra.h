#pragma once

//returns array `len` where `len[i]` = shortest path from node `startNode` to node i
//For example len[startNode] will always = 0
//
//status: tested on random graphs agains floyd warshals, and on https://judge.yosupo.jp/problem/shortest_path

const ll INF = 1e18;

struct dij {
	vector<ll> len;
	vector<int> par;
};

dij dijkstra(const vector<vector<pair<int,ll>>>& adj /*directed or undirected, weighted graph*/, int startNode) {
	vector<ll> len(adj.size(), INF);
	vector<int> par(adj.size(), -1);
	len[startNode] = 0;
	set<pair<ll, int>> q;//weight, node
	q.insert({0, startNode});
	while(!q.empty()) {
		auto it = q.begin();
		const int node = it->second;
		q.erase(it);
		for(auto [to, weight] : adj[node]) {
			if(len[to] > weight + len[node]) {
				q.erase({len[to], to});
				len[to] = weight + len[node];
				par[to] = node;
				q.insert({len[to], to});
			}
		}
	}
	return dij{len, par};
}
