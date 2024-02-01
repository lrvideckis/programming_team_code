/** @file */
#pragma once
#include "monotonic_stack.hpp"
/**
 * @code{.cpp}
       vector<long long> a;
       auto mr = mono_st(a, less()), ml = mono_range(mr); // greater(), less_equal(), greater_equal()
 * @endcode
 * @param mr monotonic stack array of a
 * @returns (if you use less()) vector ml such that:
 *     - ml[i] < i < mr[i]
 *     - a[i] is the min of exclusive-exclusive range (ml[i], mr[i])
 *     - ml[i] is the max index such that a[ml[i]] < a[i], or -1
 *     - mr[i] is the min index such that a[i] >= a[mr[i]], or n
 * @time O(n)
 * @space two O(n) vectors are allocated and returned
 */
vector<int> mono_range(const vector<int>& mr) {
    vector ml(ssize(mr), -1);
    for (int i = 0; i < ssize(mr); i++)
        for (int j = i + 1; j != mr[i]; j = mr[j]) ml[j] = i;
    return ml;
}
