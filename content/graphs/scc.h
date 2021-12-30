#pragma once

struct scc {
public:
	scc(const vector<vector<int>>& adj) : sccId(adj.size()), numSccs(0) {
		int n = adj.size();
		stack<int> seen;
		{
			vector<bool> vis(n,false);
			for(int i = 0; i < n; ++i) {
				if(!vis[i]) {
					dfs1(i, seen, adj, vis);
				}
			}
		}
		vector<vector<int>> adjInv(n);
		for(int i = 0; i < n; ++i) {
			for(int to : adj[i]) {
				adjInv[to].push_back(i);
			}
		}
		vector<bool> vis(n,false);
		while(!seen.empty()) {
			int node = seen.top();
			seen.pop();
			if(vis[node]) {
				continue;
			}
			dfs2(node, adjInv, vis);
			numSccs++;
		}
	}
	int numberOfSCCs() const {
		return numSccs;
	}
	int getSccID(int node) const {
		return sccId[node];
	}
private:
	vector<int> sccId;
	int numSccs;
	void dfs1(int curr, stack<int>& seen, const vector<vector<int>>& adj, vector<bool>& vis) {
		vis[curr] = true;
		for(int x : adj[curr]) {
			if(!vis[x]) {
				dfs1(x, seen, adj, vis);
			}
		}
		seen.push(curr);
	}
	void dfs2(int curr, const vector<vector<int>>& adjInv, vector<bool>& vis) {
		vis[curr] = true;
		sccId[curr] = numSccs;
		for(int x : adjInv[curr]) {
			if(!vis[x]) {
				dfs2(x, adjInv, vis);
			}
		}
	}
};
