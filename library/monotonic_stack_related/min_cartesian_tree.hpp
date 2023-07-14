/** @file */
#pragma once
#include "monotonic_stack.hpp"
/**
 * 2, 1, 3, 1, 2, 0, 1, 0, 2
 * TODO: ascii art example
 * @code{.cpp}
 *     auto [le, ri] = get_range(arr);
 *     auto [root, adj] = min_cartesian_tree(arr, le, ri);
 * @endcode
 * @param arr array of integers (there can be duplicates)
 * @param le,ri arr[i] is the min of range (le[i], ri[i])
 * @returns root of tree, and adjacency list (only childs)
 * @time O(n)
 * @space this function allocates/returns an adj list which is O(n)
 */
pair<int, vector<vector<int>>> min_cartesian_tree(const vector<int>& arr, const vector<int>& le, const vector<int>& ri) {
    int n = ssize(arr);
    assert(ssize(le) == n && ssize(ri) == n);
    auto leftmost_min = [&](int i) -> bool {return le[i] == -1 || arr[le[i]] < arr[i];};
    vector<int> to_min(n);
    iota(begin(to_min), end(to_min), 0);
    for (int i = 0; i < n; i++)
        if (!leftmost_min(i))
            to_min[i] = to_min[le[i]];
    vector<vector<int>> adj(n);
    int root = -1;
    for (int i = 0; i < n; i++) {
        if (le[i] == -1 && ri[i] == n) {
            assert(root == -1);
            root = i;
        } else if (leftmost_min(i)) {
            bool le_par = (le[i] >= 0 && (ri[i] == n || arr[le[i]] > arr[ri[i]]));
            adj[to_min[le_par ? le[i] : ri[i]]].push_back(i);
        }
    }
    return {root, adj};
}
