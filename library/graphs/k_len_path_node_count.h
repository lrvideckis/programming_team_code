#pragma once
//0-based nodes
//returns array `num_paths` where `num_paths[i]` = number of paths with k nodes where node `i` is on the path
//O(n log n)
vector<long long> get_num_paths(const vector<vector<int>>& adj/*unrooted tree*/, int k) {
	int n = adj.size();
	vector<long long> num_paths(n);
	//TODO
	return num_paths;
}
