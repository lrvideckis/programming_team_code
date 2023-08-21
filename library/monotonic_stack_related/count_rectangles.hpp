/** @file */
#pragma once
#include "min_range.hpp"
/**
 * @param grid an n-by-m boolean array
 * @returns an (n+1)-by-(m+1) array cnt where cnt[i][j] = the number of times
 * an i-by-j sub rectangle appears in the matrix such that all i*j cells in the
 * sub rectangle are 1. cnt[0][j] and cnt[i][0] will contain garbage values.
 * @time O(n * m)
 * @space this function allocates/returns a O(n * m) vector
 */
vector<vector<int>> count_rectangles(const vector<vector<bool>>& grid) {
    int n = ssize(grid), m = ssize(grid[0]);
    vector cnt(n + 1, vector(m + 1, 0));
    vector arr(m, 0);
    for (const auto& row : grid) {
        transform(begin(arr), end(arr), begin(row), begin(arr), [](int a, bool g) {
            return g * (a + 1);
        });
        auto [le, ri] = min_range(arr);
        for (int j = 0; j < m; j++) {
            int cnt_l = j - le[j] - 1, cnt_r = ri[j] - j - 1;
            cnt[arr[j]][cnt_l + cnt_r + 1]++;
            cnt[arr[j]][cnt_l]--;
            cnt[arr[j]][cnt_r]--;
        }
    }
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 2; j++)
            partial_sum(rbegin(cnt[i]), rend(cnt[i]) - 1, rbegin(cnt[i]));
    for (int i = n - 1; i >= 1; i--)
        transform(begin(cnt[i]), end(cnt[i]), begin(cnt[i + 1]), begin(cnt[i]), plus{});
    return cnt;
}
