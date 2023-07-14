/** @file */
#pragma once
#include "monotonic_stack.hpp"
/**
 * @code{.cpp}
 *     auto [root, adj] = min_cartesian_tree(arr);
 * @endcode
 * @param arr array of distinct integers
 * @returns root of tree, and adjacency list (only childs)
 * @time O(n)
 * @space this function allocates/returns an adj list which is O(n)
 */
pair<int, vector<vector<int>>> min_cartesian_tree(const vector<int>& arr) {
    int n = ssize(arr);
    auto [le, ri] = get_range(arr);
    int root = -1;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        if (le[i] == -1 && ri[i] == n) {
            assert(root == -1);
            root = i;
        } else {
            bool le_par = (le[i] >= 0 && (ri[i] == n || arr[le[i]] > arr[ri[i]]));
            adj[le_par ? le[i] : ri[i]].push_back(i);
        }
    }
    assert(root != -1);
    return {root, adj};
}
