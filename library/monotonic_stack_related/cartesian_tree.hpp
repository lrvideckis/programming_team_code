/** @file */
#pragma once
#include "monotonic_range.hpp"
/**
 * either min or max cartesian tree
 */
struct cart_tree {
    /**
     * @{
     */
    int root;
    vector<vector<int>> adj;
    vector<int> le, ri, to_extrema;
    /** @} */
};
/**
 * @code{.cpp}
 *     //min cartesian tree
 *     auto [root, adj, le, ri, to_extrema] = get_cart_tree(arr, less());
 *     //max cartesian tree
 *     auto [root, adj, le, ri, to_extrema] = get_cart_tree(arr, greater());
 * @endcode
 * @param arr array of integers (there can be duplicates)
 * @returns see cart_tree
 * @time O(n)
 * @space this function allocates/returns cart_tree struct which is O(n)
 */
template <class T, class F = function<bool(T, T)>> cart_tree get_cart_tree(const vector<T>& arr, F less) {
    int n = ssize(arr);
    auto [le, ri] = mono_range(arr, less);
    vector<int> to_extrema(n);
    for (int i = n - 1; i >= 0; i--)
        to_extrema[i] = (ri[i] < n && arr[i] == arr[ri[i]]) ? to_extrema[ri[i]] : i;
    vector<vector<int>> adj(n);
    int root = -1;
    for (int i = 0; i < n; i++) {
        if (le[i] == -1 && ri[i] == n) root = i;
        else if (to_extrema[i] == i) {
            bool le_par = (le[i] != -1 && (ri[i] == n || less(arr[ri[i]], arr[le[i]])));
            adj[to_extrema[le_par ? le[i] : ri[i]]].push_back(i);
        }
    }
    return {root, adj, le, ri, to_extrema};
}
