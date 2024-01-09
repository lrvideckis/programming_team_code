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
    vector le = mono_st<T>({rbegin(a), rend(a)}, [&](T x, T y) {return !cmp(y, x);});
    reverse(begin(le), end(le));
    transform(begin(le), end(le), begin(le), [&](int i) {return ssize(a) - i - 1;});
    return {le, mono_st(a, cmp)};
}
