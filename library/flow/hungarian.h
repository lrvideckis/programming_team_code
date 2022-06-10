#pragma once
//library checker tests: https://judge.yosupo.jp/problem/assignment
//source: https://e-maxx.ru/algo/assignment_hungary
//
//input: cost[1...n][1...m] with n <= m
//n workers, indexed 1, 2, ..., n
//m jobs, indexed 1, 2, ..., m
//it costs `cost[i][j]` to assign worker i to job j (1<=i<=n, 1<=j<=m)
//this returns *min* total cost to assign each worker to some distinct job
//O(n^2 * m)
//
//trick 1: set `cost[i][j]` to INF to say: "worker `i` cannot be assigned job `j`"
//trick 2: `cost[i][j]` can be negative, so to instead find max total cost over all matchings: set all `cost[i][j]` to `-cost[i][j]`.
//Now max total cost = - HungarianMatch(cost).minCost
const long long inf = 1e18;
struct match {
	long long min_cost;
	vector<int> matching;//worker `i` (1<=i<=n) is assigned to job `matching[i]` (1<=matching[i]<=m)
};
match hungarian(const vector<vector<long long>>& cost) {
	int n = cost.size() - 1, m = cost[0].size() - 1;
	assert(n <= m);
	vector<int> p(m + 1), way(m + 1);
	vector<long long> u(n + 1), v(m + 1);
	for (int i = 1; i <= n; i++) {
		p[0] = i;
		int j0 = 0;
		vector<long long> minv(m + 1, inf);
		vector<bool> used(m + 1, false);
		do {
			used[j0] = true;
			int i0 = p[j0], j1 = 0;
			long long delta = inf;
			for (int j = 1; j <= m; j++)
				if (!used[j]) {
					long long cur = cost[i0][j] - u[i0] - v[j];
					if (cur < minv[j])
						minv[j] = cur, way[j] = j0;
					if (minv[j] < delta)
						delta = minv[j], j1 = j;
				}
			for (int j = 0; j <= m; j++)
				if (used[j])
					u[p[j]] += delta, v[j] -= delta;
				else
					minv[j] -= delta;
			j0 = j1;
		} while (p[j0] != 0);
		do {
			int j1 = way[j0];
			p[j0] = p[j1];
			j0 = j1;
		} while (j0);
	}
	vector<int> ans(n + 1);
	for (int j = 1; j <= m; j++)
		ans[p[j]] = j;
	return {-v[0], ans};
}
