/** @file */
#pragma once
/**
 * @see https://github.com/ucf-programming-team/hackpack-cpp/
 * blob/master/content/data-structures/DSURestorable.h
 *
 * DSU without path compression, so non-amortized. Most operations are O(log n)
 */
struct dsu_restorable {
	int num_sets;
	vector<int> p;
	vector<long long> subtree;
	vector<optional<array<int, 3>>> st;
	dsu_restorable(int n): num_sets(n), p(n, -1), subtree(n) {}
	int find(int u) const {
		while (p[u] >= 0) u = p[u];
		return u;
	}
	bool update(int u, int v) {
		st.emplace_back();
		if ((u = find(u)) == (v = find(v))) return 0;
		if (p[u] > p[v]) swap(u, v);
		st.back() = {u, v, p[v]};
		p[u] += p[v], p[v] = u, subtree[u] += subtree[v], num_sets--;
		return 1;
	}
	void undo() {
		assert(!st.empty());
		if (st.back()) {
			auto [u, v, sz_v] = st.back().value();
			num_sets++, subtree[u] -= subtree[v], p[v] = sz_v, p[u] -= p[v];
		}
		st.pop_back();
	}
	int size(int u) const {return -p[find(u)];}
	bool same_set(int u, int v) const {return find(u) == find(v);}
	long long sum(int u) const {return subtree[find(u)];}
	void add(int u, int d) {while (u >= 0) subtree[u] += d, u = p[u];}
};
