#pragma once

//status: not tested

#include "../math/fft.h"

const int Max = 1e6+10;
int n, sizes[Max];
vector<int> adj[Max], cntPathLength[Max];
ll cntTotalPathLengths[Max];
bool removed[Max];

void dfs2(int node, int par, int root, int currDist) {
	while((int)cntPathLength[root].size() <= currDist) {
		cntPathLength[root].push_back(0);
	}
	cntPathLength[root][currDist]++;
	sizes[node] = 1;
	for(int to : adj[node]) {
		if(to != par && !removed[to]) {
			dfs2(to, node, root, currDist+1);
			sizes[node] += sizes[to];
		}
	}
}

int findCentroid(int node) {
	dfs2(node, node, node, 1);
	bool found = true;
	int sizeCap = sizes[node]/2;
	int par = node;
	while(found) {
		found = false;
		for(int to : adj[node]) {
			if(to != par && !removed[to] && sizes[to] > sizeCap) {
				found = true;
				par = node;
				node = to;
				break;
			}
		}
	}
	return node;
}

void dfs1(int node, int par) {
	removed[node] = true;
	int maxLength = 1;
	for(int to : adj[node]) {
		if(to != par && !removed[to]) {
			cntPathLength[to].clear();
			cntPathLength[to].push_back(0);
			dfs2(to, to, to, 1);
			maxLength = max(maxLength, (int)cntPathLength[to].size());
		}
	}
	vector<int> temp(maxLength, 0);
	temp[0]++;
	for(int to : adj[node]) {
		if(to != par && !removed[to]) {
			vector<ll> prod = multiply(temp, cntPathLength[to]);
			for(int i = 0; i < (int)prod.size(); ++i) {
				cntTotalPathLengths[i] += prod[i];
			}
			for(int i = 0; i < (int)cntPathLength[to].size(); ++i) {
				temp[i] += cntPathLength[to][i];
			}
		}
	}

	for(int to : adj[node]) {
		if(to != par && !removed[to]) {
			dfs1(findCentroid(to), node);
		}
	}
}
