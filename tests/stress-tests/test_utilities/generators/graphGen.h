#pragma once

#include "../../../../Library/misc/random.h"
#include "../../../../Library/graphs/disjointSet.h"

//https://en.wikipedia.org/wiki/Erd%C5%91s%E2%80%93R%C3%A9nyi_model
//each edge has independent probability p of existing
vector<pair<int,int>> genRandomSimpleGraph(int n, double p, bool isDirected, int maxEdges) {
	vector<pair<int,int>> edges;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(i == j) continue;
			if(!isDirected && j < i) continue;
			if(getRandReal(0,1) < p) {
				edges.push_back({i,j});
				if((int)edges.size() >= maxEdges) return edges;
			}
		}
	}
	return edges;
}
vector<vector<int>> genRandomGraph(
	int n,//0 based nodes
	bool isDirected = false,
	bool isConnected = false,
	bool isSimple = true,/*true means no self edges, and no multiple edges*/
	int maxEdges = 5000) {
	assert(!(isConnected && isDirected));//I don't feel like implementing SCC here (for strongly connectivity)
	vector<vector<int>> adj(n);
	auto addEdge = [&](int u, int v) -> void {
		adj[u].push_back(v);
		if(!isDirected) {
			adj[v].push_back(u);
		}
	};
	disjointSet ds(n);

	//see https://en.wikipedia.org/wiki/Erd%C5%91s%E2%80%93R%C3%A9nyi_model#Properties_of_G(n,_p)
	//regarding picking a probability for edge existence
	int probGenType = getRand(1,4);
	double pEdge = 0.001;
	if(probGenType == 1) {
		//expected behavior: no components with size > log(n)
		pEdge = getRandReal(0, 1/double(n));
	} else if(probGenType == 2) {
		//expected behavior: largest component has size n^(2/3)
		pEdge = 1/double(n);
	} else if(probGenType == 3) {
		//expected behavior: graph has isolated nodes, thus will be disconnected
		pEdge = getRandReal(1, log(max(n,3))) / double(n);
		pEdge = min(pEdge, 1.0);
	} else {
		assert(probGenType == 4);
		//expected behavior: graph is connected
		pEdge = getRandReal(log(n), n) / double(n);
	}

	for(auto [u,v] : genRandomSimpleGraph(n, pEdge, isDirected, maxEdges)) {
		ds.merge(u,v);
		addEdge(u,v);
	}
	if(isConnected) {
		assert(!isDirected);//sanity check
		map<int,vector<int>> sets;
		for(int i = 0; i < n; i++) sets[ds.find(i)].push_back(i);
		while(sets.size() >= 2) {
			vector<int> setOne = sets.begin()->second;
			sets.erase(sets.begin());
			vector<int> setTwo = sets.begin()->second;
			sets.erase(sets.begin());
			int u = setOne[getRand(0, (int)setOne.size()-1)];
			int v = setTwo[getRand(0, (int)setTwo.size()-1)];
			addEdge(u, v);
			assert(ds.merge(u,v));
			for(vector<int> currSet : {setOne, setTwo}) {
				for(int node : currSet) sets[ds.find(node)].push_back(node);
			}
		}
		for(int i = 1; i < n; i++) {
			assert(ds.find(0) == ds.find(i));
		}
	}
	if(!isSimple) {
		for(int numSelfEdges = getRand(0, 5); numSelfEdges--;) {
			int node = getRand(0, n-1);
			addEdge(node, node);
		}
		for(int numMultipleEdges = getRand(0,9); numMultipleEdges--;) {
			int node = getRand(0, n-1);
			if(adj[node].empty()) continue;
			int next = adj[node][getRand(0, (int)adj[node].size()-1)];
			addEdge(node, next);
		}
	}
	return adj;
}
