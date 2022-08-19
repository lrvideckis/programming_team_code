#pragma once
#include "../../kactl/content/numerical/FastFourierTransform.h"
//returns array `len` where `len[i]` = # of paths in tree with length `i`
//O(n log^2 n) -- TODO: is this correct?
vector<long long> tree_freq_dist(const vector<vector<int>>& adj/*unrooted, connected tree*/) {
	int n = adj.size();
	vector<int> vis(n, 0), sizes(n);
	vector<long long> res(n, 0);
	auto dfs_depth_cnt = [&](auto self, int node, int par, int currDist, vector<int>& cntDist) -> void {
		if ((int)cntDist.size() <= currDist) cntDist.resize(currDist + 1, 0);
		cntDist[currDist]++;

		for (int child : adj[node]) {
			if (child == par || vis[child]) continue;
			self(self, child, node, currDist + 1, cntDist);
		}
	};
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
	auto dfs = [&](auto self, int node) -> void {
		assert(!vis[node]);
		node = find_centroid(node);
		assert(!vis[node]);
		vis[node] = true;
		vector<double> totalCnt(1, 1.0);
		for (int to : adj[node]) {
			if (!vis[to]) {
				vector<int> cntDist;
				dfs_depth_cnt(dfs_depth_cnt, to, node, 1, cntDist);
				{
					vector<double> tmpCntDist(cntDist.size());
					for (int i = 0; i < (int)cntDist.size(); i++) tmpCntDist[i] = cntDist[i];
					vector<double> prod = conv(totalCnt, tmpCntDist);
					for (int i = 1; i < (int)prod.size(); i++) {
						res[i] += prod[i] + 0.5;//for rounding
					}
				}
				if (totalCnt.size() < cntDist.size()) totalCnt.resize(cntDist.size(), 0.0);
				for (int i = 1; i < (int)cntDist.size(); i++) totalCnt[i] += cntDist[i];
				self(self, to);
			}
		}
	};
	dfs(dfs, 0);
	return res;
}
