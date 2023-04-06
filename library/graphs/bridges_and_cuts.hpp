/** @file */
#pragma once
/**
 * Info about the connectivity of each node and edge
 */
struct graph_info {
	int num_2_edge_ccs; /**< number of components in bridge tree */
	vector<bool> is_bridge; /**< is_bridge[edge id] = 1 iff bridge edge */
	vector<int> two_edge_ccid; /**< two_edge_ccid[node] = id of 2 edge component (labeled 0, 1, ..., `num_2_edge_ccs`-1) */
	int num_bccs; /**< number of bi-connected components */
	vector<bool> is_cut; /**< is_cut[node] = 1 iff cut node */
	vector<int> bcc_id; /**< bcc_id[edge id] = id of bcc (which are labeled 0, 1, ..., `num_bccs`-1) */
};
/**
 * @see https://cp-algorithms.com/graph/bridge-searching.html
 *     https://cp-algorithms.com/graph/cutpoints.html
 *
 * @code{.cpp}
 *     //example initialization of `adj`:
 *     for (int i = 0; i < m; i++) {
 *         int u, v;
 *         cin >> u >> v;
 *         u--, v--;
 *         adj[u].emplace_back(v, i);
 *         adj[v].emplace_back(u, i);
 *     }
 *     auto [num_bccs, is_cut, bcc_id] = bridge_and_cut(adj, m);
 * @endcode
 * @param adj undirected graph; possibly with multiple edges
 * @param m number of edges
 * @returns info about both bridge edges and cut nodes.
 * @time O(n + m)
 * @memory O(n + m)
 */
graph_info bridge_and_cut(const vector<vector<pair<int, int>>>& adj, int m) {
	//stuff for both (always keep)
	int n = ssize(adj), timer = 1;
	vector<int> tin(n);
	//2 edge cc stuff (delete if not needed)
	int num_2_edge_ccs = 0;
	vector<bool> is_bridge(m);
	vector<int> two_edge_ccid(n), node_stack;
	node_stack.reserve(n);
	//bcc stuff (delete if not needed)
	int num_bccs = 0;
	vector<bool> is_cut(n);
	vector<int> bcc_id(m), edge_stack;
	edge_stack.reserve(m);
	auto dfs = [&](auto&& self, int u, int p_id) -> int {
		int low = tin[u] = timer++, deg = 0;
		node_stack.push_back(u);
		for (auto [v, e_id] : adj[u]) {
			if (e_id == p_id) continue;
			if (!tin[v]) {
				edge_stack.push_back(e_id);
				int low_ch = self(self, v, e_id);
				if (low_ch >= tin[u]) {
					is_cut[u] = 1;
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
			} else if (tin[v] < tin[u]) {
				edge_stack.push_back(e_id);
				low = min(low, tin[v]);
			}
		}
		if (p_id == -1) is_cut[u] = (deg > 1);
		if (tin[u] == low) {
			if (p_id != -1) is_bridge[p_id] = 1;
			while (1) {
				int node = node_stack.back();
				node_stack.pop_back();
				two_edge_ccid[node] = num_2_edge_ccs;
				if (node == u) break;
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
