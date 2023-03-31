#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum"
#include "../template.hpp"

#include "../../../library/graphs/restorable_dsu.hpp"
#include "../../../library/misc/priority_queue_undo.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	update_priority_queue<update_priority_queue, int, int> upq(RestorableDSU(n));
	for(int i = 0; i < n; i++) {
		int val;
		cin >> val;
	}
	while(q--) {
		int type;
		cin >> type;
		if(type == 0) {
			int u, v;
			cin >> u >> v;
		} else if(type == 1) {
			int u, v;
			cin >> u >> v;
		} else if(type == 2) {
			int v, x;
			cin >> v >> x;
		} else {
			assert(type == 3);
			int v;
			cin >> v;
		}
	}
	return 0;
}
