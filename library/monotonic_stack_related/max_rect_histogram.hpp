/** @file */
#pragma once
#include "monotonic_range.hpp"
/**
 * @param arr contains positive integers
 * @returns largest integer x such that there exists a subarray arr[le,ri)
 * with: (ri-le) * min(arr[le,ri)) == x
 * @time O(n)
 * @space besides O(n) param `arr`, O(n) extra space is allocated temporarily
 */
long long max_rect_histogram(const vector<int>& arr) {
    auto [le, ri] = mono_range(arr, less());
    auto max_area = 0LL;
    for (int i = 0; i < ssize(arr); i++)
        max_area = max(max_area, 1LL * arr[i] * (ri[i] - le[i] - 1));
    return max_area;
}
