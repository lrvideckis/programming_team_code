/** @file */
#pragma once
#include "monotonic_stack.hpp"
/**
 * @param arr array of distinct integers
 * @returns array par where par[v] = parent of node v in min-cartesian-tree.
 * par[v] == -1 iff arr[v] == min(arr)
 * @time O(n)
 * @memory O(n)
 */
vector<int> cartesian_tree(const vector<int>& arr) {
    int n = ssize(arr);
    vector<int> left = monotonic_stack<int>(arr, less());
    vector<int> right = monotonic_stack<int>(vector<int>(rbegin(arr), rend(arr)), less());
    vector<int> par(n);
    transform(begin(left), end(left), rbegin(right), begin(par), [&](int le, int ri) {
        ri = n - 1 - ri;
        if (le >= 0 && ri < n) return arr[le] > arr[ri] ? le : ri;
        if (le >= 0) return le;
        if (ri < n) return ri;
        return -1;
    });
    return par;
}
