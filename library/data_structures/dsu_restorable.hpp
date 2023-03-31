/** @file */
#pragma once
/**
 * @see https://github.com/ucf-programming-team/hackpack-cpp/
 * blob/master/content/data-structures/DSURestorable.h
 */
struct dsu_restorable {
	vector<int> p; /**< parent */
	vector<long long> subtree; /**< sum of node values in subtree */
	vector<optional<array<int, 3>>> st; /**< stack of updates/joins */
	/**
	 * @param n number of nodes
	 * @time O(n)
	 */
	dsu_restorable(int n): p(n, -1), subtree(n) {}
	/**
	 * @param u a node
	 * @returns representative of u's disjoint set
	 * @time O(log n)
	 */
	int find(int u) const {
		while (p[u] >= 0) u = p[u];
		return u;
	}
	/**
	 * @param u a node
	 * @param d delta to add to node u's value
	 * @time O(log n)
	 */
	void add(int u, int d) {
		while (u >= 0) subtree[u] += d, u = p[u];
	}
	/**
	 * @param u,v 2 nodes
	 * @returns 1 iff we successfully joined their disjoint sets
	 * @time O(log n)
	 */
	bool update(int u, int v) {
		st.emplace_back();
		if ((u = find(u)) == (v = find(v))) return 0;
		if (p[u] > p[v]) swap(u, v);
		st.back() = {u, v, p[v]};
		p[u] += p[v], p[v] = u, subtree[u] += subtree[v];
		return 1;
	}
	/**
	 * undo the last update/join
	 * @time O(1)
	 */
	void undo() {
		assert(!st.empty());
		if (st.back()) {
			auto [u, v, sz_v] = st.back().value();
			subtree[u] -= subtree[v], p[v] = sz_v, p[u] -= p[v];
		}
		st.pop_back();
	}
	/**
	 * @param u,v 2 nodes
	 * @returns 1 iff u and v are in the same disjoint set
	 * @time O(log n)
	 */
	bool same(int u, int v) const {return find(u) == find(v);}
	/**
	 * @param u a node
	 * @returns number of nodes in u's disjoint set
	 * @time O(log n)
	 */
	int size(int u) const {return -p[find(u)];}
	/**
	 * @param u a node
	 * @returns sum of values of nodes in u's disjoint set
	 * @time O(log n)
	 */
	long long sum(int u) const {return subtree[find(u)];}
};
