/** @file */
#pragma once
/**
 * The stuff calculated by hopcroft_karp.
 */
struct match {
	int size_of_matching; /**< # of edges in max matching (which = size of min vertex cover by König's theorem) */
	/**
	 * edge node_left <=> l_to_r[node_left] in matching iff l_to_r[node_left] != -1
	 * ditto r_to_l[node_right] <=> node_right
	 */
	/** @{ */
	vector<int> l_to_r, r_to_l;
	/** @} */
	/**
	 * mvc_l[node_left] = 1 iff node_left is in the min vertex cover; ditto mvc_r[node_right]
	 * mvc_l[node_left] = 0 iff node_left is in the max independent set
	 */
	/** @{ */
	vector<bool> mvc_l, mvc_r;
	/** @} */
};
/**
 * @see https://github.com/foreverbell/acm-icpc-cheat-sheet/
 *     blob/master/src/graph-algorithm/hopcroft-karp.cpp
 *
 * @code{.cpp}
 *     //0 <= node_left < lsz
 *     //0 <= node_right < rsz
 *     //for every edge node_left <=> node_right
 *     adj[node_left].push_back(node_right);
 * @endcode
 * @param adj bipartite graph
 * @param rsz number of nodes on right side
 * @returns info about max matching, and min vertix cover
 * @time O(m * sqrt(n)) n = lsz + rsz
 * @memory O(n + m)
 */
match hopcroft_karp(const vector<vector<int>>& adj, int rsz) {
	int size_of_matching = 0, lsz = ssize(adj);
	vector<int> l_to_r(lsz, -1), r_to_l(rsz, -1);
	while (1) {
		queue<int> q;
		vector<int> level(lsz, -1);
		for (int i = 0; i < lsz; i++)
			if (l_to_r[i] == -1)
				level[i] = 0, q.push(i);
		bool found = 0;
		vector<bool> mvc_l(lsz, 1), mvc_r(rsz, 0);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			mvc_l[u] = 0;
			for (auto x : adj[u]) {
				mvc_r[x] = 1;
				int v = r_to_l[x];
				if (v == -1) found = 1;
				else if (level[v] == -1) {
					level[v] = level[u] + 1;
					q.push(v);
				}
			}
		}
		if (!found) return {size_of_matching, l_to_r, r_to_l, mvc_l, mvc_r};
		auto dfs = [&](auto self, int u) -> bool {
			for (auto x : adj[u]) {
				int v = r_to_l[x];
				if (v == -1 || (level[u] + 1 == level[v] && self(self, v))) {
					l_to_r[u] = x;
					r_to_l[x] = u;
					return 1;
				}
			}
			level[u] = 1e9;
			return 0;
		};
		for (int i = 0; i < lsz; i++)
			size_of_matching += (l_to_r[i] == -1 && dfs(dfs, i));
	}
}
