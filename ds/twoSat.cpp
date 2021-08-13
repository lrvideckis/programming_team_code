struct twosat {
	int n, sccID;
	vector<vector<int>> adj, adjInv;
	vector<int> scc;
	vector<bool> visited, assignment;
	stack<int> seen;

	twosat(int variables) : n(2*variables), adj(n), adjInv(n), scc(n), assignment(variables) {}

	//X AND Y = (X OR X) AND (Y OR Y)
	//X NAND Y = (!X OR !Y)
	//X NOR Y = (!X OR !X) AND (!Y OR !Y)
	//X XOR Y = (X OR Y) AND (!X OR !Y)
	//X XNOR Y = (!Y OR X) AND (!X OR Y)
	void add(int i, bool statusI, int j, bool statusJ) {
		int from1 = i+(!statusI)*(n/2);
		int to1 = j+statusJ*(n/2);
		adj[from1].push_back(to1);
		adjInv[to1].push_back(from1);
		int from2 = j+(!statusJ)*(n/2);
		int to2 = i+statusI*(n/2);
		adj[from2].push_back(to2);
		adjInv[to2].push_back(from2);
	}

	void dfs1(int curr) {
		visited[curr] = true;
		for(int x : adj[curr]) {
			if(!visited[x]) {
				dfs1(x);
			}
		}
		seen.push(curr);
	}

	void dfs2(int curr) {
		visited[curr] = true;
		scc[curr] = sccID;
		for(int x : adjInv[curr]) {
			if(!visited[x]) {
				dfs2(x);
			}
		}
	}

	bool solve() {
		visited.resize(n, false);
		for(int i = 0; i < n; ++i) {
			if(!visited[i]) {
				dfs1(i);
			}
		}
		sccID = 0;
		visited.assign(n, false);
		while(!seen.empty()) {
			int node = seen.top();
			seen.pop();
			if(!visited[node]) {
				dfs2(node);
				sccID++;
			}
		}
		for(int i = 0; i < n/2; ++i) {
			if(scc[i] == scc[i+n/2]) {
				return false;
			}
			assignment[i] = scc[i] < scc[i+n/2];
		}
		return true;
	}
};
