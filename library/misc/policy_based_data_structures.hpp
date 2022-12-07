/** @file */
#pragma once
/**
 * Place these includes *before* the `#define int long long` else compile error.
 * not using <bits/extc++.h> as it compile errors on codeforces c++20 compiler
 */
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
/**
 * @see https://codeforces.com/blog/entry/11080
 *
 * BST with extra functions
 * order_of_key - # of elements *strictly* less than given element
 * find_by_order - find kth largest element, k is 0 based so find_by_order(0) returns min element
 */
template <typename T> using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
indexed_set<pair<long long, int>> is; /**< example initialization */
/**
 * @see https://codeforces.com/blog/entry/60737
 *
 * apparently faster than unordered_map
 */
gp_hash_table<string, long long> ht;
