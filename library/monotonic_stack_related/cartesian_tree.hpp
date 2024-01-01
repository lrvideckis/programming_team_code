/** @file */
#pragma once
#include "monotonic_range.hpp"
/**
 * either min or max cartesian tree
 */
struct cart_tree {
    /**
     * min cartesian tree
     * a = {2, 1, 3, 1, 0, 1, 2, 2, 0, 2}
     *     (------------------------x---)
     *     (---------x)   (x------) | (x)
     *     (x)   (x) |     | (---x) |  |
     *      |     |  |     |     |  |  |
     * idx: 0  1  2  3  4  5  6  7  8  9
     * root = 8; (note root can = -1 iff a is empty)
     * u | adj[u]
     * 8 | 3, 5, 9
     * 3 | 0, 2
     * 5 | 7
     * indexes 1, 4, 6 are not nodes as they are not the right-most extrema of their subarrays
     * to_extrema[1] = 3
     * to_extrema[4] = 8
     * to_extrema[6] = 7
     * else to_extrema[i] = i
     * @{
     */
    int root;
    vector<vector<int>> adj;
    vector<int> le, ri, to_extrema;
    /** @} */
};
/**
 * @code{.cpp}
       //min cartesian tree
       auto [root, adj, le, ri, to_extrema] = get_cart_tree(a, less());
       //max cartesian tree
       auto [root, adj, le, ri, to_extrema] = get_cart_tree(a, greater());
 * @endcode
 * @param a array of integers (there can be duplicates)
 * @param cmp comparator
 * @returns see cart_tree
 * @time O(n)
 * @space this function allocates/returns cart_tree struct which is O(n)
 */
template <class T, class F> cart_tree get_cart_tree(const vector<T>& a, F cmp) {
    int n = ssize(a);
    auto [le, ri] = mono_range(a, cmp);
    vector<int> to_extrema(n);
    for (int i = n - 1; i >= 0; i--)
        to_extrema[i] = (ri[i] < n && a[i] == a[ri[i]]) ? to_extrema[ri[i]] : i;
    vector<vector<int>> adj(n);
    int root = -1;
    for (int i = 0; i < n; i++)
        if (le[i] == -1 && ri[i] == n) root = i;
        else if (to_extrema[i] == i) {
            bool le_par = (le[i] != -1 && (ri[i] == n || cmp(a[ri[i]], a[le[i]])));
            adj[to_extrema[le_par ? le[i] : ri[i]]].push_back(i);
        }
    return {root, adj, le, ri, to_extrema};
}
