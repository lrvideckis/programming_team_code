/** @file */
#pragma once
#include "monotonic_stack.hpp"
/**
 * @param arr contains positive integers
 * @returns largest integer x such that there exists a subarray arr[le,ri)
 * with: (ri-le) * min(arr[le,ri)) == x
 * @time O(n)
 * @memory O(n)
 */
long long max_rect_histogram(const vector<int>& arr) {
    auto rv = [&](int i) -> int {
        return ssize(arr) - 1 - i;
    };
    vector<int> left = monotonic_stack<int>(arr, less());
    vector<int> right = monotonic_stack<int>(vector<int>(rbegin(arr), rend(arr)), less());
    long long max_area = 0;
    for (int i = 0; i < ssize(arr); i++) {
        int le = left[i], ri = rv(right[rv(i)]);//arr[i] is the max of range (le, ri)
        max_area = max(max_area, 1LL * arr[i] * (ri - le - 1));
    }
    return max_area;
}
