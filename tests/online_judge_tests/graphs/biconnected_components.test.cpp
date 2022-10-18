#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"
#include "../template.hpp"

#include "../../../library/graphs/block_vertex_tree.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	vector<vector<pair<int, int>>> adj(n);
	vector<pair<int, int>> edges(m);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].emplace_back(v, i);
		adj[v].emplace_back(u, i);
		edges[i] = make_pair(u, v);
	}
	graph_info cc = bridge_and_cut(adj, m);
	vector<vector<int>> bvt = block_vertex_tree(adj, cc);
	for (int i = 0; i < n; i++) {
		//cut node if there exists a pair of adjacent edges belonging to different BCCs
		bool is_cut = 0;
		for (int j = 0; j < ssize(adj[i]); j++) {
			if (cc.bcc_id[adj[i][0].second] != cc.bcc_id[adj[i][j].second])
				is_cut = 1;
		}
		assert(is_cut == cc.is_cut[i]);
	}
	//check correctness of block vertex tree
	for (int i = 0; i < n; i++) {
		assert(ssize(adj[i]) >= ssize(bvt[i]));//in particular, if adj[i].empty(), then bct[i].empty()
		assert(cc.is_cut[i] == (ssize(bvt[i]) > 1));//is cut means non-leaf in block vertex tree
	}
	{
		vector<set<int>> bcc_to_nodes(cc.num_bccs), node_to_bccs(n);
		for (int i = 0; i < m; i++) {
			int bccid = cc.bcc_id[i];
			for (int node : {
			            edges[i].first, edges[i].second
			        }) {
				bcc_to_nodes[bccid].insert(node);
				node_to_bccs[node].insert(bccid);
			}
		}
		// testing commented loops in block_vertex_tree
		for (int v = 0; v < n; v++) {
			assert(ssize(node_to_bccs[v]) == ssize(bvt[v]));
			for (int bccid : bvt[v]) {
				bccid -= n;
				assert(node_to_bccs[v].count(bccid));
			}
		}
		for (int bccid = 0; bccid < cc.num_bccs; bccid++) {
			assert(ssize(bcc_to_nodes[bccid]) == ssize(bvt[bccid + n]));
			for (int v : bvt[bccid + n])
				assert(bcc_to_nodes[bccid].count(v));
		}
	}
	vector<int> lone_nodes;
	for (int v = 0; v < n; v++)
		if (bvt[v].empty()) lone_nodes.push_back(v);
	cout << cc.num_bccs + ssize(lone_nodes) << endl;
	for (int bccid = 0; bccid < cc.num_bccs; bccid++) {
		cout << ssize(bvt[bccid + n]) << " ";
		for (int v : bvt[bccid + n])
			cout << v << " ";
		cout << '\n';
	}
	for (int v : lone_nodes) cout << "1 " << v << '\n';
	return 0;
}
