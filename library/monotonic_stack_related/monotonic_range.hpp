/** @file */
#pragma once
#include "monotonic_stack.hpp"
/**
 * @code{.cpp}
       vector<long long> a;
       auto [le, ri] = mono_range(a, less()); //or greater(), less_equal(), greater_equal()
 * @endcode
 * @param a array
 * @param cmp comparator
 * @returns (if you pass in less()) vectors le, ri such that:
 *     - le[i] < i < ri[i]
 *     - a[i] is the min of exclusive-exclusive range (le[i], ri[i])
 *     - le[i] is the max index such that a[le[i]] < a[i], or -1
 *     - ri[i] is the min index such that a[i] >= a[ri[i]], or n
 * @time O(n)
 * @space two O(n) vectors are allocated and returned
 */
template <class T, class F> array<vector<int>, 2> mono_range(const vector<T>& a, F cmp) {
    vector le(ssize(a), -1), ri = mono_st(a, cmp);
    for (int i = 0; i < ssize(a); i++)
        for (int j = i + 1; j != ri[i]; j = ri[j]) le[j] = i;
    return {le, ri};
}
