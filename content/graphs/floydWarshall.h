#pragma once

//status: tested against output of dijkstras on random graphs

vector<vector<long long>> floydWarshall(const vector<vector<pair<int, long long>>>& adj /*directed or undirected, weighted graph*/) {
	int n = adj.size();
	vector<vector<long long>> len(n, vector<long long> (n, 1e18));
	for (int i = 0; i < n; i++) {
		len[i][i] = 0;//remove this line if you want shortest cycle - len[i][i] will = length of shortest cycle including node i (only for directed graphs)
		for (auto [neighbor, weight] : adj[i])
			len[i][neighbor] = min(len[i][neighbor], weight);
	}
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				len[i][j] = min(len[i][j], len[i][k] + len[k][j]);
		}
	}
	return len;
}
