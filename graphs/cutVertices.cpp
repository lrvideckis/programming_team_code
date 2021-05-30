struct cutNodes {
	public:
		cutNodes(const vector<vector<int>> &adj) : visited(adj.size(),false), cutNode(adj.size(),false), timeIn(adj.size(),adj.size()), minTime(adj.size(),adj.size()), currTime(0) {
			for(int i = 0; i < (int)adj.size(); ++i) {
				if(!visited[i]) {
					dfs(i,i,adj);
				}
			}
		}
		bool isCutNode(int node) {
			return cutNode[node];
		}

	private:
		vector<bool> visited, cutNode;
		vector<int> timeIn, minTime;
		int currTime;
		void dfs(int node, int prev, const vector<vector<int>> &adj) {
			visited[node] = true;
			timeIn[node] = minTime[node] = ++currTime;
			int numChildren = 0;
			for(int to : adj[node]) {
				if(to != prev) {
					minTime[node] = min(minTime[node], timeIn[to]);
				}
				if(visited[to]) continue;
				numChildren++;
				if(node == prev && numChildren > 1) {
					cutNode[node] = true;
				}
				dfs(to, node, adj);
				minTime[node] = min(minTime[node], minTime[to]);
				if(node != prev && minTime[to] >= timeIn[node]) {
					cutNode[node] = true;
				}
			}
		}
};
