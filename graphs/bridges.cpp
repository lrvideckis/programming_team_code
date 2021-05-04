//requires disjoint set struct
//handles multiple components, multiple edges between the same pair of nodes
//0-based nodes
struct bridges {
	public:
		bridges(const vector<vector<int>> &adj) : n(adj.size()), currTime(0), ds(adj.size()), timeIn(adj.size()), low(adj.size()) {
			for(int i = 0; i < (int)adj.size(); ++i) {
				if(!timeIn[i]) {
					dfs(adj, i, -1);
				}
			}
		}
		int getNodeId(int node) {
			return ds.find(node);
		}
		vector<pair<int, int>> getBridges() {
			return bridgeList;
		}
		int sizeOfBCC(int node) {
			return ds.sizeOfSet(node);
		}
		vector<vector<int>> getBridgeAdj() {
			vector<vector<int>> bridgeTree(n);
			for(const pair<int,int> &p : getBridges()) {
				int u = ds.find(p.first);
				int v = ds.find(p.second);
				if(u == v) continue;
				bridgeTree[u].push_back(v);
				bridgeTree[v].push_back(u);
			}
			return bridgeTree;
		}

	private:
		int n, currTime;
		disjointSet ds;
		vector<int> timeIn, low;
		vector<pair<int, int>> bridgeList;
		void dfs(const vector<vector<int>> &adj, int node, int prev) {
			timeIn[node] = low[node] = ++currTime;
			bool dup = false;
			for(int to : adj[node]) {
				if(to == prev && !dup) {
					dup = true;
					continue;
				}
				if(!timeIn[to]) {
					dfs(adj, to, node);
					if(low[to] > timeIn[node]) {
						bridgeList.push_back({to,node});
					} else {
						ds.merge(to,node);
					}
				}
				low[node] = min(low[node], low[to]);
			}
		}
};
