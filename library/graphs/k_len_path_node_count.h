#pragma once

struct centroid_decomp {
	vector<vector<int>> adj;
	function<void(const vector<vector<int>>&, int)> func;
	vector<int> subtree_sizes;

	centroid_decomp(const vector<vector<int>>& a_adj,
	                const function<void(const vector<vector<int>>&, int)>& a_func)
		: adj(a_adj), func(a_func), subtree_sizes(adj.size()) {
		decomp(find_centroid(0));
	}

	void calc_subtree_sizes(int u, int p = -1) {
		subtree_sizes[u] = 1;
		for (auto v : adj[u]) {
			if (v == p)
				continue;
			calc_subtree_sizes(v, u);
			subtree_sizes[u] += subtree_sizes[v];
		}
	}

	int find_centroid(int root) {
		calc_subtree_sizes(root);
		auto dfs = [&](auto self, int u, int p) -> int {
			int biggest_ch = -1;
			for (auto v : adj[u]) {
				if (v == p)
					continue;
				if (biggest_ch == -1 ||
				        subtree_sizes[biggest_ch] < subtree_sizes[v])
					biggest_ch = v;
			}

			if (biggest_ch != -1 &&
			        2 * subtree_sizes[biggest_ch] > subtree_sizes[root])
				return self(self, biggest_ch, u);
			return u;
		};
		return dfs(dfs, root, root);
	}

	void decomp(int root) {
		func(adj, root);
		for (auto v : adj[root]) {
			adj[v].erase(find(adj[v].begin(), adj[v].end(), root));
			decomp(find_centroid(v));
		}
	}
};

//0-based nodes
//returns array `num_paths` where `num_paths[i]` = number of paths with k edges where node `i` is on the path
//O(n log n)
vector<long long> get_num_paths(const vector<vector<int>>& a_adj/*unrooted tree*/, int k) {
	vector<long long> num_paths(a_adj.size());
	auto func = [&](const vector<vector<int>>& adj, int root) {
		vector<int> pre_d(1, 1), cur_d(1);
		auto dfs = [&](auto self, int u, int p, int d, int rot) -> long long {
			if (d > k)
				return 0;

			if (int(cur_d.size()) <= d)
				cur_d.push_back(0);
			cur_d[d]++;

			long long cnt = 0;
			if (k - d < int(pre_d.size()))
				cnt += pre_d[k - d];

			auto adj_u = adj[u];
			if (rot == 1)
				reverse(adj_u.begin(), adj_u.end());

			for (int v : adj_u) {
				if (v == p)
					continue;
				cnt += self(self, v, u, d + 1, rot);
				if (u == root) {
					for (int i = 1; i < int(cur_d.size()) && cur_d[i]; i++) {
						if (int(pre_d.size()) <= i)
							pre_d.push_back(0);
						pre_d[i] += cur_d[i];
						cur_d[i] = 0;
					}
				}
			}

			num_paths[u] += cnt;
			return cnt;
		};
		dfs(dfs, root, root, 0, 0);
		pre_d = vector<int>(1);
		cur_d = vector<int>(1);
		num_paths[root] -= dfs(dfs, root, root, 0, 1);
	};
	centroid_decomp decomp(a_adj, func);
	return num_paths;
}
