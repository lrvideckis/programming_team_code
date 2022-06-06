#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"
#include "../../template.h"

#include "../../../Library/graphs/bridges_and_cuts.h"
#include "../../../Library/graphs/block_vertex_tree.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	vector<vector<pair<int,int>>> adj(n);
	vector<pair<int,int>> edges(m);
	for(int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].emplace_back(v, i);
		adj[v].emplace_back(u, i);
		edges[i] = make_pair(u, v);
	}

	info cc = bridge_and_cut(adj, m);
	vector<vector<int>> bvt = block_vertex_tree(adj, cc);

	for(int i = 0; i < n; i++) {
		//cut node if there exists a pair of adjacent edges belonging to different BCCs
		bool isCut = false;
		for(int j = 0; j < (int)adj[i].size(); j++) {
			if(cc.bccID[adj[i][0].second] != cc.bccID[adj[i][j].second]) {
				isCut = true;
			}
		}
		assert(isCut == cc.isCut[i]);
	}



	//check correctness of block vertex tree
	for(int i = 0; i < n; i++) {
		assert(cc.isCut[i] == (bvt[i].size() > 1));//is cut means non-leaf in block vertex tree

		set<int> curr_bccs;
		for(auto [to, eId] : adj[i]) {
			int bccid = cc.bccID[eId];
			curr_bccs.insert(bccid);
		}
		assert(curr_bccs.size() == bvt[i].size());
		for(int bccid : bvt[i]) {
			bccid -= n;
			assert(curr_bccs.count(bccid));
		}
	}

	{
		vector<set<int>> bccToNodes(cc.numBCCs);
		for(int i = 0; i < m; i++) {
			auto [u, v] = edges[i];
			bccToNodes[cc.bccID[i]].insert(u);
			bccToNodes[cc.bccID[i]].insert(v);
		}

		for(int bccid = 0; bccid < cc.numBCCs; bccid++) {
			assert(bccToNodes[bccid].size() == bvt[bccid+n].size());
			for(int i : bvt[bccid + n]) {
				assert(bccToNodes[bccid].count(i));
			}
		}
	}

	cout << cc.numBCCs << endl;
	vector<vector<int>> ccs(cc.numBCCs);
	for(int i = 0; i < m; i++) {
		ccs[cc.bccID[i]].push_back(i);
	}
	for(auto& cc : ccs) {
		cout << cc.size() << " ";
		for(int node : cc) cout << node << " ";
		cout << endl;
	}

	return 0;
}
