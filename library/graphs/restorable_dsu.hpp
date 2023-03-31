/** @file */
#pragma once
/**
 * @see https://github.com/ucf-programming-team/hackpack-cpp/
 * blob/master/content/data-structures/DSURestorable.h
 */
struct restorable_dsu {
	vector<int> p/*parent*/;
	vector<long long> subtree;
	vector<vector<pair<int, int>>> st;//TODO: find better way to represent an update
	restorable_dsu(int n): p(n, -1), subtree(n) {}
	int find(int u) const {
		while(p[u] >= 0) u = p[u];
		return u;
	}
	void add(int u, int d) {
		while(u >= 0) subtree[u] += d, u = p[u];
	}
	bool update(int u, int v) {
		st.emplace_back();
		u = find(u), v = find(v);
		if (u == v) return 0;
		if (p[u] > p[v]) swap(u, v);
		st.back().emplace_back(u, p[u]);
		st.back().emplace_back(v, p[v]);
		subtree[u] += subtree[v];
		p[u] += p[v], p[v] = u;
		return 1;
	}
	void undo() {
		assert(!st.empty());
		for(auto it = st.back().rbegin(); it != st.back().rend(); it++) {
			assert(it->second < 0);//TODO remove
			if(p[it->first] >= 0) subtree[p[it->first]] -= subtree[it->first];
			p[it->first] = it->second;
		}
		st.pop_back();
	}
	//TODO: add size (here and also in a test
	long long sum(int u) const { return subtree[find(u)]; }
};
