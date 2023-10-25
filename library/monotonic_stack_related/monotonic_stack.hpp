/** @file */
#pragma once
/**
 * @code{.cpp}
 *     vector<long long> arr;
 *     vector<int> le = mono_st(arr, less()); // greater(), less_equal(), greater_equal()
 * @endcode
 * @param arr array
 * @param less any transitive compare operator
 * @returns array le where le[i] = max integer such that: le[i] < i and
 * less(arr[le[i]], arr[i]). If no integer exists, le[i] = -1
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <class T, class F> vector<int> mono_st(const vector<T>& arr, F less) {
    vector<int> le(ssize(arr));
    iota(begin(le), end(le), -1);
    for (int i = 0; i < ssize(arr); i++)
        while (le[i] >= 0 && !less(arr[le[i]], arr[i])) le[i] = le[le[i]];
    return le;
}
