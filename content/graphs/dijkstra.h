#pragma once

vector<ll> dijkstra(const vector<vector<pair<int,ll>>> &adj, int startNode) {
	const int n = adj.size();
	vector<ll> length(n, 1e18);
	length[startNode] = 0;
	set<pair<ll, int> > q;//weight, node
	q.insert({0, startNode});
	while(!q.empty()) {
		auto it = q.begin();
		const int node = it->second;
		q.erase(it);
		for(auto &p : adj[node]) {
			int to = p.first;
			ll weight = p.second;
			if(length[to] > weight + length[node]) {
				q.erase({length[to], to});
				length[to] = weight + length[node];
				q.insert({length[to], to});
			}
		}
	}
	return length;
}
