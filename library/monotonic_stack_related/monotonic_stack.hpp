/** @file */
#pragma once
/**
 * @code{.cpp}
 *     vector<T> arr;
 *     vector<int> le = monotonic_stack(arr, less()); //less, less_equal, greater, greater_equal
 * @endcode
 * @param arr array
 * @param less any transitive compare operator
 * @returns array le where le[i] = max integer such that: le[i] < i and
 * less(arr[le[i]], arr[i]). If no integer exists, le[i] = -1
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <class T, class F> vector<int> monotonic_stack(const vector<T>& arr, F less) {
    vector<int> le(ssize(arr));
    iota(begin(le), end(le), -1);
    for (int i = 0; i < ssize(arr); i++)
        while (le[i] >= 0 && !less(arr[le[i]], arr[i])) le[i] = le[le[i]];
    return le;
}
