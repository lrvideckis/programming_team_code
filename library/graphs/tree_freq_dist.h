#pragma once
#include "../../kactl/content/numerical/FastFourierTransform.h"
//returns array `len` where `len[i]` = # of paths in tree with length `i`
//O(n log^2 n)
vector<long long> tree_freq_dist(const vector<vector<int>>& adj/*unrooted, connected tree*/) {
	int n = adj.size();
	vector<int> vis(n, 0), sizes(n);
	auto dfs_sz = [&](auto self, int node, int par) -> void {
		sizes[node] = 1;
		for (int child : adj[node]) {
			if (child == par || vis[child]) continue;
			self(self, child, node);
			sizes[node] += sizes[child];
		}
	};
	auto find_centroid = [&](int node) -> int {
		dfs_sz(dfs_sz, node, node);
		int size_cap = sizes[node] / 2, par = -1;
		while (1) {
			bool found = 0;
			for (int to : adj[node]) {
				if (to != par && !vis[to] && sizes[to] > size_cap) {
					found = 1;
					par = node;
					node = to;
					break;
				}
			}
			if (!found) return node;
		}
	};
	vector<long long> res(n, 0);
	auto dfs = [&](auto self, int node) -> void {
		node = find_centroid(node);
		vis[node] = 1;
		vector<double> total_cnt(1, 1.0);
		for (int to : adj[node]) {
			if (!vis[to]) {
				vector<double> cnt_dist(1, 0.0);
				{
					queue<pair<int, int>> q;
					q.emplace(to, node);
					while (!q.empty()) {
						cnt_dist.push_back(q.size());
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
				}
				{
					vector<double> prod = conv(total_cnt, cnt_dist);
					for (int i = 1; i < (int)prod.size(); i++) res[i] += (long long)(prod[i] + 0.5);
				}
				if (total_cnt.size() < cnt_dist.size()) total_cnt.resize(cnt_dist.size(), 0.0);
				for (int i = 1; i < (int)cnt_dist.size(); i++) total_cnt[i] += cnt_dist[i];
				self(self, to);
			}
		}
	};
	dfs(dfs, 0);
	return res;
}
