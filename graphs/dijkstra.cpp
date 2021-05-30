vector<int> dijkstra(const vector<vector<pair<int,int>>> &adj, int startNode) {
	const int n = adj.size();
	vector<int> length(n, 1e9);
	length[startNode] = 0;
	set<pair<int, int> > q;//weight, node
	q.insert({0, startNode});
	while(!q.empty()) {
		auto it = q.begin();
		const int node = it->second;
		q.erase(it);
		for(auto &p : adj[node]) {
			int to = p.first;
			int weight = p.second;
			if(length[to] > weight + length[node]) {
				q.erase({length[to], to});
				length[to] = weight + length[node];
				q.insert({length[to], to});
			}
		}
	}
	return length;
}
