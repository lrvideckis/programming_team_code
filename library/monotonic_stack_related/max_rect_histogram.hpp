/** @file */
#pragma once
#include "monotonic_stack.hpp"
/**
 * @param a contains positive integers
 * @returns largest integer x such that there exists a subarray a[le,ri)
 * with: (ri-le) * min(a[le,ri)) == x
 * @time O(n)
 * @space besides O(n) param `a`, O(n) extra space is allocated temporarily
 */
long long max_rect_histogram(const vector<int>& a) {
    auto ri = mono_st(a, less());
    auto max_area = 0LL;
    for (int i = 0; i < ssize(a); i++)
        for (int j = i + 1; j != ri[i]; j = ri[j])
            max_area = max(max_area, 1LL * a[j] * (ri[j] - i - 1));
    return max_area;
}
