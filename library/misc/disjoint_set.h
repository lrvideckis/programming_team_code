#pragma once
//library checker tests: https://judge.yosupo.jp/problem/unionfind
//stress tests: tests/stress_tests/graphs/disjoint_set.cpp
struct disjointSet {
	int numSets;
	vector<int> par;
	disjointSet(int n) : numSets(n), par(n, -1) {}
	disjointSet(const disjointSet& rhs) : numSets(rhs.numSets), par(rhs.par) {}
	int find(int x) {
		return par[x] < 0 ? x : par[x] = find(par[x]);
	}
	int sizeOfSet(int x) {
		return -par[find(x)];
	}
	bool merge(int x, int y) {
		if ((x = find(x)) == (y = find(y))) return false;
		if (par[y] < par[x]) swap(x, y);
		par[x] += par[y];
		par[y] = x;
		numSets--;
		return true;
	}
};
