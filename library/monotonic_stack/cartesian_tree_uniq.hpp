/** @file */
#pragma once
#include "monotonic_stack.hpp"
/**
 * @code{.cpp}
       auto ri = mono_st(a, less()), p = cart_tree_uniq(ri); // min cart tree
       auto ri = mono_st(a, greater()), p = cart_tree_uniq(ri); // max cart tree
 * @endcode
 * @param ri monotonic stack of an array *with unique values*
 * @returns parent array
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
vector<int> cart_tree_uniq(const vector<int>& ri) {
    vector<int> p(ri);
    for (int i = 0; i < ssize(p); i++)
        for (int j = i + 1; j != ri[i]; j = ri[j])
            if (ri[j] == ri[i]) p[j] = i;
    return p;
}
