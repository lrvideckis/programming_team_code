#pragma once
const long long INF = 1e18;
struct weighted_match {
	long long min_cost;
	vector<int> matching;//worker `i` (1<=i<=n) is assigned to job `matching[i]` (1<=matching[i]<=m)
};
/**
 * Given cost[1...n][1...m] with 1 <= n <= m.
 * n workers, indexed 1, 2, ..., n
 * m jobs, indexed 1, 2, ..., m
 * It costs `cost[i][j]` to assign worker i to job j (1<=i<=n, 1<=j<=m). This
 * returns *min* sum of costs to assign each worker to some distinct job.
 *
 * Set `cost[i][j]` to INF to say: "worker i cannot be assigned job j".
 * This works for negatives, so negating cost array gives max matching.
 *
 * @see https://e-maxx.ru/algo/assignment_hungary
 * @time O(n^2 * m)
 * @memory O(n * m)
 */
weighted_match hungarian(const vector<vector<long long>>& cost) {
	int n = ssize(cost) - 1, m = ssize(cost[0]) - 1;
	assert(n <= m);
	vector<int> p(m + 1), way(m + 1);
	vector<long long> u(n + 1), v(m + 1);
	for (int i = 1; i <= n; i++) {
		p[0] = i;
		int j0 = 0;
		vector<long long> minv(m + 1, INF);
		vector<bool> used(m + 1, 0);
		do {
			used[j0] = 1;
			int i0 = p[j0], j1 = 0;
			long long delta = INF;
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
