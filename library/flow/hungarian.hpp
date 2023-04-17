/** @file */
#pragma once
/**
 * Represents a matching: number of edges is maximized (with pairwise distinct
 * nodes). Of all ways to do this, sum of edge weights is minimized.
 */
struct weighted_match {
    long long min_weight; /**< sum of edge weights in matching */
    vector<int> l_to_r; /**< edge v <=> l_to_r[v] is in the matching, 1<=v<=n; 1<=l_to_r[v]<=m */
};
/**
 * @see https://e-maxx.ru/algo/assignment_hungary
 *
 * nodes on left side: 1, 2, ..., n
 * nodes on right side: 1, 2, ..., m
 * n <= m
 * @param cost (n+1)-by-(m+1) array: cost[u][v] = weight (can be negative) of
 * the edge u <=> v, 1<=u<=n; 1<=v<=m
 * @returns min matching
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
        vector<long long> minv(m + 1, LLONG_MAX);
        vector<bool> used(m + 1);
        do {
            used[j0] = 1;
            int i0 = p[j0], j1 = 0;
            long long delta = LLONG_MAX;
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
    vector<int> l_to_r(n + 1);
    for (int j = 1; j <= m; j++) l_to_r[p[j]] = j;
    return {-v[0], l_to_r};
}
