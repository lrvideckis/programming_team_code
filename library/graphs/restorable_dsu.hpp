/** @file */
#pragma once
/**
 * @see https://github.com/ucf-programming-team/hackpack-cpp/
 * blob/master/content/data-structures/DSURestorable.h
 */
struct restorable_dsu {
	vector<int> p/*parent*/;
	vector<long long> subtree;
	vector<optional<tuple<int, int, int>>> st;
	restorable_dsu(int n): p(n, -1), subtree(n) {}
	int find(int u) const {
		while (p[u] >= 0) u = p[u];
		return u;
	}
	void add(int u, int d) {
		while (u >= 0) subtree[u] += d, u = p[u];
	}
	bool update(int u, int v) {
		st.emplace_back();
		u = find(u), v = find(v);
		if (u == v) return 0;
		if (p[u] > p[v]) swap(u, v);
		st.back().emplace(u, v, p[v]);
		subtree[u] += subtree[v];
		p[u] += p[v], p[v] = u;
		return 1;
	}
	void undo() {
		assert(!st.empty());
		if (st.back()) {
			auto [u, v, sz_v] = st.back().value();
			p[v] = sz_v;
			p[u] -= p[v];
			subtree[u] -= subtree[v];
		}
		st.pop_back();
	}
	//TODO: add size (here and also in a test
	long long sum(int u) const {return subtree[find(u)];}
};
