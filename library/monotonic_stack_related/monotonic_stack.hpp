/** @file */
#pragma once
/**
 * @code{.cpp}
 *     vector<int> arr;
 *     vector<int> le = monotonic_stack(arr, less()); //less, less_equal, greater, greater_equal
 * @endcode
 * @param arr array
 * @param less any transitive compare operator
 * @returns array le where le[i] = max integer such that: le[i] < i and
 * less(arr[le[i]], arr[i]). If no integer exists, le[i] = -1
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <typename F> vector<int> monotonic_stack(const vector<int>& arr, F less) {
    vector<int> le(ssize(arr));
    iota(begin(le), end(le), -1);
    for (int i = 0; i < ssize(arr); i++)
        while (le[i] >= 0 && !less(arr[le[i]], arr[i])) le[i] = le[le[i]];
    return le;
}
/**
 * @code{.cpp}
 *     vector<int> arr;
 *     auto [le, ri] = get_range(arr);
 * @endcode
 * @param arr array
 * @returns vectors le, ri such that:
 *     - le[i] < i < ri[i]
 *     - arr[i] is the min of exclusive-exclusive range (le[i], ri[i])
 *     - le[i] is the max index such that arr[le[i]] <= arr[i], or -1
 *     - ri[i] is the min index such that arr[i] > arr[ri[i]], or n
 * @time O(n)
 * @space O(n)
 */
pair<vector<int>, vector<int>> get_range(const vector<int>& arr) {
    vector<int> le = monotonic_stack(arr, less_equal());
    vector<int> ri = monotonic_stack(vector<int>(rbegin(arr), rend(arr)), less());
    reverse(begin(ri), end(ri));
    transform(begin(ri), end(ri), begin(ri), [&](int val) {return ssize(arr) - val - 1;});
    return {le, ri};
}
