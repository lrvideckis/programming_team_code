/** @file */
#pragma once
/**
 * @code{.cpp}
       vector<long long> a;
       auto mr = mono_st(a, less()); // greater(), less_equal(), greater_equal()
       for (int i = n - 1; i >= 0; i--)
           for (int j = i + 1; j != mr[i]; j = mr[j])
               // for all k in [j, mr[j]): cmp(a[i], a[k])
               // these ranges are disjoint, and union to [i + 1, mr[i])
 * @endcode
 * @param a array
 * @param cmp any transitive compare operator
 * @returns array mr where mr[i] = max integer such that:
 *     for all k in [i + 1, mr[i]): cmp(a[i], a[k])
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <class T, class F> vector<int> mono_st(const vector<T>& a, F cmp) {
    vector<int> mr(ssize(a));
    for (int i = ssize(a) - 1; i >= 0; i--)
        for (mr[i] = i + 1; mr[i] < ssize(a) && cmp(a[i], a[mr[i]]);) mr[i] = mr[mr[i]];
    return mr;
}
