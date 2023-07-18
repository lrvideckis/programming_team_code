/** @file */
#pragma once
#include "../../../data_structures/sparse_table.hpp"
#include "../suffix_array.hpp"
#include "../longest_common_prefix_array.hpp"
/**
 * Various queries you can do based on suffix array.
 * @code{.cpp}
 *     string s;
 *     sa_query saq(s, 256);
 *     vector<int> arr;
 *     sa_query saq(arr, 100'005);
 * @endcode
 */
template <typename T> struct sa_query {
    T s;
    vector<int> sa, sa_inv, lcp;
    RMQ<int> rmq_sa, rmq_lcp;
    /**
     * @param a_s,max_val string/array with 0 <= s[i] < max_val
     * @time O((n log n) + max_val)
     * @space O(n log n) for RMQ's; a O(max_val) vector `freq` is used temporarily during get_sa
     */
    sa_query(const T& a_s, int max_val) : s(a_s) {
        tie(sa, sa_inv) = get_sa(s, max_val);
        lcp = get_lcp_array(s, sa, sa_inv);
        rmq_sa = RMQ<int>(sa, [](int x, int y) -> int {return min(x, y);});
        rmq_lcp = RMQ<int>(lcp, [](int x, int y) -> int {return min(x, y);});
    }
};
