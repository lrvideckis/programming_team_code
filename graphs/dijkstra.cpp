const int N = 5e5+5;//change here
vector<pair<ll, ll>> adj[N];
ll length[N];

void dijkstra(int node) {
	length[node] = 0;
	set<pair<ll, int> > q;//weight, node
	q.insert({0, node});
	while(!q.empty()) {
		auto it = q.begin();
		node = it->second;
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
}
