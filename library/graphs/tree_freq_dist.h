#pragma once
#include "../../kactl/content/numerical/FastFourierTransform.h"
//returns array `cnt_paths` where `cnt_paths[i]` = # of paths in tree with `i` edges
//centroid decomposition + FFT
//O(n log^2 n)
vector<long long> tree_freq_dist(const vector<vector<int>>& adj/*unrooted, connected tree*/) {
	int n = adj.size();
	vector<int> vis(n, 0), sizes(n);
	auto dfs_sz = [&](auto self, int node, int par) -> void {
		sizes[node] = 1;
		for (int ch : adj[node]) {
			if (ch == par || vis[ch]) continue;
			self(self, ch, node);
			sizes[node] += sizes[ch];
		}
	};
	auto find_centroid = [&](int node) -> int {
		dfs_sz(dfs_sz, node, -1);
		int size_cap = sizes[node] / 2, par = -1;
		while (1) {
			bool found = 0;
			for (int ch : adj[node]) {
				if (ch != par && !vis[ch] && sizes[ch] > size_cap) {
					found = 1;
					par = node;
					node = ch;
					break;
				}
			}
			if (!found) return node;
		}
	};
	vector<long long> cnt_paths(n, 0);
	auto dfs = [&](auto self, int node) -> void {
		node = find_centroid(node);
		vis[node] = 1;
		vector<double> total_depth(1, 1.0);
		for (int to : adj[node]) {
			if (vis[to]) continue;
			vector<double> cnt_depth(1, 0.0);
			for (queue<pair<int, int>> q({{to, node}}); !q.empty();) {
				cnt_depth.push_back(q.size());
				queue<pair<int, int>> new_q;
				while (!q.empty()) {
					auto [curr, par] = q.front();
					q.pop();
					for (int ch : adj[curr]) {
						if (ch == par || vis[ch]) continue;
						new_q.emplace(ch, curr);
					}
				}
				swap(q, new_q);
			}
			{
				vector<double> prod = conv(total_depth, cnt_depth);
				for (int i = 1; i < (int)prod.size(); i++) cnt_paths[i] += llround(prod[i]);
			}
			if (total_depth.size() < cnt_depth.size()) total_depth.resize(cnt_depth.size(), 0.0);
			for (int i = 1; i < (int)cnt_depth.size(); i++) total_depth[i] += cnt_depth[i];
			self(self, to);
		}
	};
	dfs(dfs, 0);
	return cnt_paths;
}
