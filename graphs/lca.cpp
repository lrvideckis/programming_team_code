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
	lca(const vector<vector<pair<int, ll>>> &graph, int root) :
		depth(graph.size()), dist(graph.size()), Log(1) {//0 - based nodes
			int n = graph.size();
			while((1<<Log) < n) ++Log;
			memo.resize(n,vector<int>(Log));
			dfs(root,root,graph);
		}

	void dfs(int node, int par, const vector<vector<pair<int, ll>>> &graph) {
		memo[node][0] = par;
		for(int i = 1; i < Log; ++i)
			memo[node][i] = memo[memo[node][i-1]][i-1];
		for(const auto [to, w] : graph[node]) {
			if(to == par) continue;
			depth[to] = 1 + depth[node];
			dist[to] = w + dist[node];
			dfs(to, node, graph);
		}
	}

	int kthPar(int node, int k) {
		for(int bit = 0; bit < Log; ++bit)
			if(k&(1<<bit))
				node = memo[node][bit];
		return node;
	}

	int getLca(int x, int y) {
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

	int distEdges(int x, int y) {
		return depth[x] + depth[y] - 2 * depth[getLca(x,y)];
	}

	ll distWeight(int x, int y) {
		return dist[x] + dist[y] - 2 * dist[getLca(x,y)];
	}
};
