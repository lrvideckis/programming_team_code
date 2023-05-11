/** @file */
#pragma once
#include "suffix_array.hpp"
#include "../data_structures/sparse_table.hpp"
/**
 * @see https://github.com/yosupo06/Algorithm/blob
 * /master/src/string/suffixarray.hpp
 *
 * Various queries you can do based on suffix array.
 */
template <typename T> struct sa_query {
    T s; /**< initial string */
    suffix_array<T> info; /**< stores raw arrays */
    /**
     * needed for various queries
     * @{
     */
    RMQ<int> rmq_lcp, rmq_sa;
    /** @} */
    /**
     * @param a_s,max_val string/array with 0 <= a_s[i] < max_val
     * @time O((nlogn) + max_val)
     * @space O((nlogn) + max_val)
     */
    sa_query(const T& a_s, int max_val) :
        s(a_s),
        info(suffix_array(s, max_val)),
        rmq_lcp(info.lcp, [](int i, int j) -> int {return min(i, j);}),
        rmq_sa(info.sa, [](int i, int j) -> int {return min(i, j);}) {}
    /**
     * @param idx1,idx2 starting 0-based-indexes of suffixes
     * @returns max integer k such that s.substr(idx1, k) == s.substr(idx2, k)
     * @time O(1)
     */
    inline int get_lcp(int idx1, int idx2) const {
        if (idx1 == idx2) return ssize(s) - idx1;
        auto [le, ri] = minmax(info.rank[idx1], info.rank[idx2]);
        return rmq_lcp.query(le, ri);
    }
    /**
     * @param idx1,idx2 starting 0-based-indexes of suffixes
     * @returns 1 iff suffix s.substr(idx1) < s.substr(idx2)
     * @time O(1)
     */
    inline bool less(int idx1, int idx2) const {
        return info.rank[idx1] < info.rank[idx2];
    }
    /**
     * @param t needle
     * @returns range [le, ri) such that:
     * - for all i in [le, ri): t == s.substr(info.sa[i], ssize(t))
     * - `ri - le` is the # of matches of t in s.
     * @time O(|t| * log(|s|))
     */
    pair<int, int> find(const T& t) const {
        auto cmp = [&](int i, int cmp_val) -> bool {
            return s.compare(i, ssize(t), t) < cmp_val;
        };
        auto le = lower_bound(begin(info.sa), end(info.sa), 0, cmp);
        auto ri = lower_bound(le, end(info.sa), 1, cmp);
        return {le - begin(info.sa), ri - begin(info.sa)};
    }
    /**
     * @param t needle
     * @returns min i such that t == s.substr(i, ssize(t)) or -1. For example,
     * replace RMQ with kth-smallest PST/Wavelet to solve
     * https://open.kattis.com/problems /anothersubstringqueryproblem
     * @time O(|t| * log(|s|))
     */
    int find_first(const T& t) const {
        auto [le, ri] = find(t);
        if (le == ri) return -1;
        return rmq_sa.query(le, ri);
    }
};
