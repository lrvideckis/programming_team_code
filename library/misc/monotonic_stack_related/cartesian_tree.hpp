/** @file */
#pragma once
#include "monotonic_stack.hpp"
/**
 * @code{.cpp}
 *     vector<int> par = cartesian_tree(arr, less()); //min cartesian tree
 *     vector<int> par = cartesian_tree(arr, greater()); //max cartesian tree
 * @endcode
 * @param arr array of distinct integers
 * @param less any transitive compare operator
 * @returns array par where par[v] = parent of node v in min-cartesian-tree.
 * par[v] == -1 iff arr[v] == min(arr)
 * @time O(n)
 * @memory O(n)
 */
template <typename F> vector<int> cartesian_tree(const vector<int>& arr, const F& less) {
    int n = ssize(arr);
    vector<int> left = monotonic_stack(arr, less);
    vector<int> right = monotonic_stack(vector<int>(rbegin(arr), rend(arr)), less);
    vector<int> par(n);
    transform(begin(left), end(left), rbegin(right), begin(par), [&](int le, int ri) {
        ri = n - 1 - ri;
        if (le >= 0 && ri < n) return less(arr[le], arr[ri]) ? ri : le;
        if (le >= 0) return le;
        if (ri < n) return ri;
        return -1;
    });
    return par;
}
