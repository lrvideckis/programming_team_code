#include "../../template.h"
#include "../../random.h"

#include "../../../library/misc/dsu.h"

int cnt = 0;
void dfs(int node, const vector<vector<int>>& adj, vector<bool>& vis) {
	assert(!vis[node]);
	vis[node] = true;
	cnt++;
	for(int next : adj[node]) {
		if(!vis[next]) {
			dfs(next, adj, vis);
		}
	}
}

int main() {
	for(int tests = 20; tests--;) {
		int n = getRand(1,100);
		DSU ds(n);
		vector<vector<int>> adj(n);
		for(int ops = 1000; ops--;) {
			int type = getRand(1, 4);
			if(type == 1) {//join, add edge update
				int u = getRand(0, n-1), v = getRand(0, n-1);
				vector<bool> vis(n,false);
				dfs(u, adj, vis);
				assert(ds.join(u,v) == !vis[v]);
				adj[u].push_back(v);
				adj[v].push_back(u);
			} else if(type == 2) {//size of set, component query
				vector<bool> vis(n,false);
				for(int i = 0; i < n; i++) {
					if(!vis[i]) {
						cnt = 0;
						dfs(i, adj, vis);
						assert(ds.size_of_set(i) == cnt);
					}
				}
			} else if(type == 3) {//same set, component query
				int u = getRand(0, n-1), v = getRand(0, n-1);
				vector<bool> vis(n,false);
				dfs(u, adj, vis);
				assert((ds.find(u) == ds.find(v)) == vis[v]);
			} else {//number of sets, components query
				assert(type == 4);
				int cntCC = 0;
				vector<bool> vis(n,false);
				for(int i = 0; i < n; i++) {
					if(!vis[i]) {
						dfs(i, adj, vis);
						cntCC++;
					}
				}
				assert(cntCC == ds.num_sets);
			}
		}
	}

	cout << "Tests passed!" << endl;
	return 0;
}
