/** @file */
#pragma once
/**
 * @code{.cpp}
       vector<long long> a;
       vector<int> le = mono_st(a, less()); // greater(), less_equal(), greater_equal()
 * @endcode
 * @param a array
 * @param cmp any transitive compare operator
 * @returns array le where le[i] = max integer such that: le[i] < i and
 * cmp(a[le[i]], a[i]). If no integer exists, le[i] = -1
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <class T, class F> vector<int> mono_st(const vector<T>& a, F cmp) {
    vector<int> le(ssize(a));
    iota(begin(le), end(le), -1);
    for (int i = 0; i < ssize(a); i++)
        while (le[i] >= 0 && !cmp(a[le[i]], a[i])) le[i] = le[le[i]];
    return le;
}
