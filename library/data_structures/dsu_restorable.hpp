/** @file */
#pragma once
/**
 * @see https://github.com/ucf-programming-team/hackpack-cpp/
 * blob/master/content/data-structures/DSURestorable.h
 */
struct dsu_restorable {
	vector<int> s;
	vector<long long> subtree;
	vector<optional<array<int, 3>>> st;
	dsu_restorable(int n): s(n, -1), subtree(n) {}
	int find(int u) const {
		while (s[u] >= 0) u = s[u];
		return u;
	}
	void add(int u, int d) {
		while (u >= 0) subtree[u] += d, u = s[u];
	}
	bool update(int u, int v) {
		st.emplace_back();
		u = find(u), v = find(v);
		if (u == v) return 0;
		if (s[u] > s[v]) swap(u, v);
		st.back() = {u, v, s[v]};
		s[u] += s[v], s[v] = u, subtree[u] += subtree[v];
		return 1;
	}
	void undo() {
		assert(!st.empty());
		if (st.back()) {
			auto [u, v, sz_v] = st.back().value();
			subtree[u] -= subtree[v], s[v] = sz_v, s[u] -= s[v];
		}
		st.pop_back();
	}
	bool same(int u, int v) const {return find(u) == find(v);}
	long long sum(int u) const {return subtree[find(u)];}
};
