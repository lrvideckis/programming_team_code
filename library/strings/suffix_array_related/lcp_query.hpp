/** @file */
#pragma once
#include "../../data_structures/sparse_table.hpp"
#include "suffix_array.hpp"
#include "lcp_array.hpp"
/**
 * query for longest common prefix of 2 suffixes
 *
 * note if one of the suffixes is the entire string (i1 == 0 || i2 == 0)
 * then it's the same as z algorithm
 */
template <class T> struct lcp_query {
    suf sf;
    vector<int> lcp;
    RMQ<int> rmq;
    /**
     * @param s,max_val string/array with 0 <= s[i] < max_val
     * @time O((n log n) + max_val)
     * @space O(n log n) for RMQ's; a O(max_val) vector `freq` is used temporarily during get_sa
     */
    lcp_query(const T& s, int max_val) :
        sf(get_sa(s, max_val)), lcp(get_lcp_array(sf, s)),
        rmq(lcp, [](int x, int y) -> int {return min(x, y);}) {}
    /**
     * @param i1,i2 starting 0-based-indexes of suffixes
     * @returns max integer k such that s.substr(i1, k) == s.substr(i2, k)
     * @time O(1)
     * @space O(1)
     */
    inline int get_lcp(int i1, int i2) const {
        if (i1 == i2) return ssize(sf.sa) - i1;
        auto [le, ri] = minmax(sf.sa_inv[i1], sf.sa_inv[i2]);
        return rmq.query(le, ri);
    }
};
