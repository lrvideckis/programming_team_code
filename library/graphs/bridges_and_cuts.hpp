#pragma once
struct graph_info {
	//2 edge connected component stuff (e.g. components split by bridge edges)
	int num_2_edge_ccs;
	vector<bool> is_bridge;//edge id -> 1 iff bridge edge
	vector<int> two_edge_ccid;//node -> id of 2 edge component (which are labeled 0, 1, ..., `num_2_edge_ccs`-1)
	//bi connected component stuff (e.g. components split by cut/articulation nodes)
	int num_bccs;
	vector<bool> is_cut;//node -> 1 iff cut node
	vector<int> bcc_id;//edge id -> id of bcc (which are labeled 0, 1, ..., `num_bccs`-1)
};
/**
 * @code{.cpp}
 *     //example initialization of `adj`:
 *     for (int i = 0; i < m; i++) {
 *         int u, v;
 *         cin >> u >> v;
 *         u--, v--;
 *         adj[u].emplace_back(v, i);
 *         adj[v].emplace_back(u, i);
 *     }
 * @endcode
 * @see https://cp-algorithms.com/graph/bridge-searching.html
 *     https://cp-algorithms.com/graph/cutpoints.html
 * @time O(n + m)
 * @memory O(n + m)
 */
graph_info bridge_and_cut(const vector<vector<pair<int/*neighbor*/, int/*edge id*/>>>& adj/*undirected graph*/, int m/*number of edges*/) {
	//stuff for both (always keep)
	int n = ssize(adj), timer = 1;
	vector<int> tin(n, 0);
	//2 edge cc stuff (delete if not needed)
	int num_2_edge_ccs = 0;
	vector<bool> is_bridge(m, 0);
	vector<int> two_edge_ccid(n), node_stack;
	node_stack.reserve(n);
	//bcc stuff (delete if not needed)
	int num_bccs = 0;
	vector<bool> is_cut(n, 0);
	vector<int> bcc_id(m), edge_stack;
	edge_stack.reserve(m);
	auto dfs = [&](auto self, int v, int p_id) -> int {
		int low = tin[v] = timer++, deg = 0;
		node_stack.push_back(v);
		for (auto [to, e_id] : adj[v]) {
			if (e_id == p_id) continue;
			if (!tin[to]) {
				edge_stack.push_back(e_id);
				int low_ch = self(self, to, e_id);
				if (low_ch >= tin[v]) {
					is_cut[v] = 1;
					while (1) {
						int edge = edge_stack.back();
						edge_stack.pop_back();
						bcc_id[edge] = num_bccs;
						if (edge == e_id) break;
					}
					num_bccs++;
				}
				low = min(low, low_ch);
				deg++;
			} else if (tin[to] < tin[v]) {
				edge_stack.push_back(e_id);
				low = min(low, tin[to]);
			}
		}
		if (p_id == -1) is_cut[v] = (deg > 1);
		if (tin[v] == low) {
			if (p_id != -1) is_bridge[p_id] = 1;
			while (1) {
				int node = node_stack.back();
				node_stack.pop_back();
				two_edge_ccid[node] = num_2_edge_ccs;
				if (node == v) break;
			}
			num_2_edge_ccs++;
		}
		return low;
	};
	for (int i = 0; i < n; i++)
		if (!tin[i])
			dfs(dfs, i, -1);
	return {num_2_edge_ccs, is_bridge, two_edge_ccid, num_bccs, is_cut, bcc_id};
}
