struct lca {
	int Log;
	vector<vector<int>> memo;
	vector<int> depth;

	lca(const vector<vector<int>> &graph, int root) {//0 - based nodes
		int n = graph.size();
		Log = 1;
		while((1<<Log) < n) ++Log;
		depth.resize(n,0);
		memo.resize(n,vector<int>(Log));
		dfs(root,root,graph);
	}

	void dfs(int node, int par, const vector<vector<int>> &graph) {
		memo[node][0] = par;
		for(int i = 1; i < Log; ++i) {
			memo[node][i] = memo[memo[node][i-1]][i-1];
		}
		for(int to : graph[node]) {
			if(to == par) continue;
			depth[to] = 1 + depth[node];
			dfs(to, node, graph);
		}
	}

	int kthPar(int node, int k) {
		for(int bit = 0; bit < Log; ++bit) {
			if(k&(1<<bit)) {
				node = memo[node][bit];
			}
		}
		return node;
	}

	int getLca(int x, int y) {
		if(depth[x] < depth[y]) swap(x,y);
		int diff = depth[x] - depth[y];
		for(int bit = 0; bit < Log; ++bit) {
			if(diff&(1<<bit)) {
				x = memo[x][bit];
			}
		}
		for(int bit = Log-1; bit >= 0; --bit) {
			if(memo[x][bit] != memo[y][bit]) {
				x = memo[x][bit];
				y = memo[y][bit];
			}
		}
		if(x != y) x = memo[x][0];
		return x;
	}

	int distEdges(int x, int y) {
		return depth[x] + depth[y] - 2 * depth[getLca(x,y)];
	}
};
