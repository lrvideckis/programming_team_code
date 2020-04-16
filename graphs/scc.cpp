struct scc {
	int n;
	vector<vector<int> > adj, adjInv;
	vector<int> sccId;
	int currScc=0;
	vector<bool> visited;

	void dfs1(int curr, stack<int> &seen) {
		visited[curr] = true;
		for(int x : adj[curr]) {
			if(!visited[x]) {
				dfs1(x, seen);
			}
		}
		seen.push(curr);
	}

	void dfs2(int curr) {
		visited[curr] = true;
		sccId[curr] = currScc;
		for(int x : adjInv[curr]) {
			if(!visited[x]) {
				dfs2(x);
			}
		}
	}

	scc(const vector<vector<int>> &graph) {
		adj = graph;
		n = adj.size();
		adjInv.resize(n);
		for(int i = 0; i < n; ++i) {
			for(int to : graph[i]) {
				adjInv[to].push_back(i);
			}
		}
		visited.resize(n,false);
		stack<int> seen;
		for(int i = 0; i < n; ++i) {
			if(!visited[i]) {
				dfs1(i, seen);
			}
		}
		visited.assign(n,false);
		sccId.resize(n);
		while(!seen.empty()) {
			if(visited[seen.top()]) {
				seen.pop();
				continue;
			}
			dfs2(seen.top());
			currScc++;
		}
	}
};
