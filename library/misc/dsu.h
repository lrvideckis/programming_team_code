#pragma once
//library checker tests: https://judge.yosupo.jp/problem/unionfind, https://judge.yosupo.jp/problem/two_edge_connected_components
//stress tests: tests/stress_tests/misc/disjoint_set.cpp
//NOLINTNEXTLINE(readability-identifier-naming)
struct DSU {
	int num_sets;
	vector<int> par;
	DSU(int n) : num_sets(n), par(n, -1) {}
	DSU(const DSU& rhs) : num_sets(rhs.num_sets), par(rhs.par) {}
	int find(int x) {
		return par[x] < 0 ? x : par[x] = find(par[x]);
	}
	int size_of_set(int x) {
		return -par[find(x)];
	}
	bool join(int x, int y) {
		if ((x = find(x)) == (y = find(y))) return false;
		if (par[y] < par[x]) swap(x, y);
		par[x] += par[y];
		par[y] = x;
		num_sets--;
		return true;
	}
};
