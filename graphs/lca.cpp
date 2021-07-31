/*
 * Description: Lowest Common Ancestor (LCA) implemented with Binary Lifting.
 * Supports functionality like kth Parent, distance between pair of nodes in
 * number of edges, and distance between pair of nodes in sum of edge weight.
 * Time: O(n * log(n)) for construction and all queries can be answered in
 * O(log(n))
 */


struct lca {
	typedef long long ll;
	int Log;
	vector<vector<int>> memo;
	vector<int> depth, dist;

	// use weights of 1 for unweighted tree
	lca(const vector<vector<pair<int, ll>>> &graph, const int root) :
		depth(n), dist(n) {//0 - based nodes
			int n = graph.size();
			Log = 1;
			while((1<<Log) < n) ++Log;
			memo.resize(n,vector<int>(Log));
			dfs(root,root,graph);
		}

	void dfs(const int node, const int par, const vector<vector<pair<int, ll>>>
			&graph) {
		memo[node][0] = par;
		for(int i = 1; i < Log; ++i)
			memo[node][i] = memo[memo[node][i-1]][i-1];
		for(const auto &[to, w] : graph[node]) {
			if(to == par) continue;
			depth[to] = 1 + depth[node];
			dist[to] = w + dist[node];
			dfs(to, node, graph);
		}
	}

	int kthPar(const int node, const int k) {
		for(int bit = 0; bit < Log; ++bit)
			if(k&(1<<bit))
				node = memo[node][bit];
		return node;
	}

	int getLca(const int x, const int y) {
		if(depth[x] < depth[y]) swap(x,y);
		x = kthPar(x, depth[x] - depth[y]);
		if(x == y) return x;
		for(int bit = Log-1; bit >= 0; --bit)
			if(memo[x][bit] != memo[y][bit]) {
				x = memo[x][bit];
				y = memo[y][bit];
			}
		assert(x != y && memo[x][0] == memo[y][0]);
		return memo[x][0];
	}

	int distEdges(const int x, const int y) {
		return dist[x] + dist[y] - 2 * depth[getLca(x,y)];
	}

	ll distWeight(const int x, const int y) {
		return dist[x] + dist[y] - 2 * dist[getLca(x,y)];
	}
};
