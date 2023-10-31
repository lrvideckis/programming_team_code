/** @file */
#pragma once
#include "monotonic_stack.hpp"
/**
 * @code{.cpp}
 *     vector<long long> arr;
 *     auto [le, ri] = mono_range(arr, less()); //or greater(), less_equal(), greater_equal()
 * @endcode
 * @param arr array
 * @param cmp comparator
 * @returns (if you pass in less()) vectors le, ri such that:
 *     - le[i] < i < ri[i]
 *     - arr[i] is the min of exclusive-exclusive range (le[i], ri[i])
 *     - le[i] is the max index such that arr[le[i]] < arr[i], or -1
 *     - ri[i] is the min index such that arr[i] >= arr[ri[i]], or n
 * @time O(n)
 * @space two O(n) vectors are allocated and returned
 */
template <class T, class F> array<vector<int>, 2> mono_range(const vector<T>& arr, F cmp) {
    vector le = mono_st(arr, cmp);
    vector ri = mono_st<T>({rbegin(arr), rend(arr)}, [&](T x, T y) {return !cmp(y, x);});
    reverse(begin(ri), end(ri));
    transform(begin(ri), end(ri), begin(ri), [&](int val) {return ssize(arr) - val - 1;});
    return {le, ri};
}
