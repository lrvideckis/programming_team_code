/** @file */
#pragma once
#include "monotonic_stack.hpp"
/**
 * @code{.cpp}
 *     vector<int> arr;
 *     auto [le, ri] = min_range(arr);
 * @endcode
 * @param arr array
 * @returns vectors le, ri such that:
 *     - le[i] < i < ri[i]
 *     - arr[i] is the min of exclusive-exclusive range (le[i], ri[i])
 *     - le[i] is the max index such that arr[le[i]] <= arr[i], or -1
 *     - ri[i] is the min index such that arr[i] > arr[ri[i]], or n
 * @time O(n)
 * @space two O(n) vectors are allocated and returned
 */
array<vector<int>, 2> min_range(const vector<int>& arr) {
    vector le = monotonic_stack(arr, less_equal());
    vector ri = monotonic_stack({rbegin(arr), rend(arr)}, less());
    reverse(begin(ri), end(ri));
    transform(begin(ri), end(ri), begin(ri), [&](int val) {return ssize(arr) - val - 1;});
    return {le, ri};
}
