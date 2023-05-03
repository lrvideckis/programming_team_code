/** @file */
#pragma once
#include "monotonic_stack.hpp"
/**
 * @param grid an n-by-m boolean array
 * @returns an (n+1)-by-(m+1) array cnt where cnt[i][j] = the number of times
 * an i-by-j sub rectangle appears in the matrix such that all i*j cells in the
 * sub rectangle are 1. cnt[0][j] and cnt[i][0] will contain garbage values.
 * @time O(n * m)
 * @memory O(n * m)
 */
vector<vector<int>> count_rectangles(const vector<vector<bool>>& grid) {
    int n = ssize(grid), m = ssize(grid[0]);
    vector<vector<int>> cnt(n + 1, vector<int>(m + 1));
    vector<int> arr(m);
    auto rv = [&](int j) -> int {
        return m - 1 - j;
    };
    for (const auto& row : grid) {
        transform(begin(arr), end(arr), begin(row), begin(arr), [](int a, bool g) {
            return g * (a + 1);
        });
        vector<int> left = monotonic_stack<int>(arr, less());
        vector<int> right = monotonic_stack<int>(vector<int>(rbegin(arr), rend(arr)), less_equal());
        for (int j = 0; j < m; j++) {
            int le = j - left[j] - 1, ri = rv(right[rv(j)]) - j - 1;
            cnt[arr[j]][le + ri + 1]++;
            cnt[arr[j]][le]--;
            cnt[arr[j]][ri]--;
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 2; j++)
            partial_sum(rbegin(cnt[i]), rend(cnt[i]) - 1, rbegin(cnt[i]));
    for (int i = n - 1; i >= 1; i--)
        transform(begin(cnt[i]), end(cnt[i]), begin(cnt[i + 1]), begin(cnt[i]), plus{});
    return cnt;
}
