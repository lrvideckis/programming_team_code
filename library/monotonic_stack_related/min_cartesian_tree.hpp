/** @file */
#pragma once
#include "min_range.hpp"
/**
 * min cartesian tree
 */
struct min_tree {
    /**
     * arr = {2, 1, 3, 1, 0, 2, 2, 1, 0, 2}
     *       (------------x---------------)
     *       (---x------) | (------x)   (x)
     *       (x) | (x)    | (x---) |     |
     *        |  |  |     |  |     |     |
     * index: 0  1  2  3  4  5  6  7  8  9
     * root = 4; note root = -1 iff arr is empty
     * u | adj[u]
     * 4 | 1, 7, 9
     * 1 | 0, 2
     * 7 | 5
     * indexes 3, 6, 8 are not nodes, as they are not the left-most min of their subarrays
     * to_min[3] = 1
     * to_min[6] = 5
     * to_min[8] = 4
     * else to_min[i] = i
     * @{
     */
    int root;
    vector<vector<int>> adj;
    vector<int> le, ri, to_min;
    /** @} */
};
/**
 * @code{.cpp}
 *     auto [root, adj, le, ri, to_min] = min_cartesian_tree(arr);
 *     queue<int> q;
 *     if (root != -1) q.push(root);
 *     while (!q.empty()) {
 *         int u = q.front();
 *         q.pop();
 *         //arr[u] is the leftmost min of exclusive-exclusive range (le[u], ri[u])
 *         for (int v : adj[u])
 *             q.push(v);
 *     }
 * @endcode
 * @param arr array of integers (there can be duplicates)
 * @returns see min_tree
 * @time O(n)
 * @space this function allocates/returns min_tree struct which is O(n)
 */
template<class T> min_tree min_cartesian_tree(const vector<T>& arr) {
    int n = ssize(arr);
    auto [le, ri] = min_range(arr);
    vector<int> to_min(n);
    for (int i = 0; i < n; i++)
        to_min[i] = (0 <= le[i] && arr[le[i]] == arr[i]) ? to_min[le[i]] : i;
    vector<vector<int>> adj(n);
    int root = -1;
    for (int i = 0; i < n; i++) {
        if (le[i] == -1 && ri[i] == n) root = i;
        else if (to_min[i] == i) {
            bool le_par = (0 <= le[i] && (ri[i] == n || arr[le[i]] > arr[ri[i]]));
            adj[to_min[le_par ? le[i] : ri[i]]].push_back(i);
        }
    }
    return {root, adj, le, ri, to_min};
}
