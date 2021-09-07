//modified from https://github.com/nealwu/competitive-programming/blob/master/graph_theory/biconnected_components.cc
struct biconnected_components {
	biconnected_components(const vector<vector<int>> &adj) :
		is_cut(adj.size(), false),
		n(adj.size()),
		tour(0),
		tour_start(n),
		low_link(n),
		visited(n, false)
	{
		for (int i = 0; i < n; i++)
			if (!visited[i])
				dfs(i, -1, adj);
	}

	bool is_bridge_edge(int u, int v) const {
		if(u > v) swap(u,v);
		return is_bridge.count(1LL * u * n + v);
	}

	//vector of all bridge edges
	vector<pair<int,int>> bridges;

	//vector of all BCCs. Note a node can be in multiple BCCs (iff it's a cut node)
	vector<vector<int>> components;

	//is_cut[`node`] is true iff `node` is a cut node
	vector<bool> is_cut;


	//use anything below this at your own risk :)
	int n, tour;
	vector<int> tour_start, low_link, stack;
	vector<bool> visited;
	unordered_set<ll> is_bridge;

	void add_bridge(int u, int v) {
		if(u > v) swap(u,v);
		is_bridge.insert(1LL * u * n + v);
	}

	void dfs(int node, int parent, const vector<vector<int>> &adj) {
		assert(!visited[node]);
		visited[node] = true;
		tour_start[node] = tour++;
		low_link[node] = tour_start[node];
		is_cut[node] = false;
		int parent_count = 0, children = 0;

		for (int next : adj[node]) {
			// Skip the first edge to the parent, but allow multi-edges.
			if (next == parent && parent_count++ == 0)
				continue;
			if (visited[next]) {
				// next is a candidate for low_link.
				low_link[node] = min(low_link[node], tour_start[next]);
				if (tour_start[next] < tour_start[node])
					stack.push_back(node);
			} else {
				int size = (int)stack.size();
				dfs(next, node, adj);
				children++;
				// next is part of our subtree.
				low_link[node] = min(low_link[node], low_link[next]);
				if (low_link[next] > tour_start[node]) {
					// This is a bridge.
					bridges.push_back({node, next});
					add_bridge(node, next);
					components.push_back({node, next});
				} else if (low_link[next] == tour_start[node]) {
					// This is the root of a biconnected component.
					stack.push_back(node);
					components.push_back(vector<int>(stack.begin() + size, stack.end()));
					stack.resize(size);
				} else {
					stack.push_back(node);
				}
				// In general, `node` is a cut vertex iff it has a child whose subtree cannot reach above `node`.
				if (low_link[next] >= tour_start[node])
					is_cut[node] = true;
			}
		}
		// The root of the tree is a cut vertex iff it has more than one child.
		if (parent < 0) {
			is_cut[node] = children > 1;
		}
	}
};


// Note: instead of a block-cut tree this is technically a block-vertex tree, which ends up being much easier to use.
// block-cut tree:
//     nodes for each BCC, and for each cut node
//     edges between a BCC and cut node iff that cut node is in that BCC (so no edges between 2 cut nodes, or 2 BCCs)
//
// block-vertex tree:
//     nodes for each BCC, and for each original node in graph
//     edges between an original node and BCC if that node is inside that BCC
struct block_cut_tree {
	block_cut_tree(const biconnected_components &_bi_comps) :
		n(_bi_comps.n),
		BC(_bi_comps.components.size()),
		T(n + BC),
		block_vertex_tree(T),
		parent(T, -1),
		depth(T)
	{
		auto add_edge = [&](int a, int b) {
			assert((a < n) ^ (b < n));
			block_vertex_tree[a].push_back(b);
			block_vertex_tree[b].push_back(a);
		};

		for (int bc = 0; bc < BC; bc++)
			for (int x : _bi_comps.components[bc])
				add_edge(x, n + bc);

		for (int root = 0; root < T; root++)
			if (parent[root] < 0)
				dfs(root, -1);
	}

	bool same_biconnected_component(int a, int b) const {
		if (depth[a] > depth[b])
			swap(a, b);
		// Two different nodes are in the same biconnected component iff their distance = 2 in the block-cut tree.
		return a == b || (depth[b] == depth[a] + 2 && parent[parent[b]] == a) || (parent[a] >= 0 && parent[a] == parent[b]);
	}

	//use anything below this at your own risk :)
	int n, BC, T;
	vector<vector<int>> block_vertex_tree;//adjacency list of block vertex tree
	vector<int> parent;
	vector<int> depth;

	void dfs(int node, int par) {
		parent[node] = par;
		depth[node] = par < 0 ? 0 : depth[par] + 1;
		for (int neigh : block_vertex_tree[node])
			if (neigh != par)
				dfs(neigh, node);
	}
};
