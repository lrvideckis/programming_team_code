/** @file */
#pragma once
#include "../data_structures/sparse_table.hpp"
/**
 * Various queries you can do based on suffix array.
 * @code{.cpp}
 *     auto [sa, rank, lcp] = get_suffix_array(s, 128);
 *     sa_query saq(s, sa, rank, lcp);
 * @endcode
 */
template <typename T> struct sa_query {
    T s;
    vector<int> sa, rank, lcp;
    RMQ<int> rmq_lcp, rmq_sa;
    /**
     * @param a_s,a_sa,a_rank,a_lcp a string and its suffix,lcp arrays
     * @time O(n log n)
     * @space O(n log n) for RMQ's
     */
    sa_query(const T& a_s, const vector<int>& a_sa, const vector<int>& a_rank, const vector<int>& a_lcp) :
        s(a_s), sa(a_sa), rank(a_rank), lcp(a_lcp),
        rmq_lcp(lcp, [](int i, int j) -> int {return min(i, j);}),
        rmq_sa(sa, [](int i, int j) -> int {return min(i, j);}) {}
    /**
     * @param idx1,idx2 starting 0-based-indexes of suffixes
     * @returns max integer k such that s.substr(idx1, k) == s.substr(idx2, k)
     * @time O(1)
     * @space O(1)
     */
    inline int get_lcp(int idx1, int idx2) const {
        if (idx1 == idx2) return ssize(s) - idx1;
        auto [le, ri] = minmax(rank[idx1], rank[idx2]);
        return rmq_lcp.query(le, ri);
    }
    /**
     * @param idx1,idx2 starting 0-based-indexes of suffixes
     * @returns 1 iff suffix s.substr(idx1) < s.substr(idx2)
     * @time O(1)
     * @space O(1)
     */
    inline bool less(int idx1, int idx2) const {
        return rank[idx1] < rank[idx2];
    }
    /**
     * @see https://github.com/yosupo06/Algorithm/blob /master/src/string/suffixarray.hpp
     * @param t needle
     * @returns range [le, ri) such that:
     * - for all i in [le, ri): t == s.substr(sa[i], ssize(t))
     * - `ri - le` is the # of matches of t in s.
     * @time O(|t| * log(|s|))
     * @space O(1)
     */
    pair<int, int> find(const T& t) const {
        auto cmp = [&](int i, int cmp_val) -> bool {
            return s.compare(i, ssize(t), t) < cmp_val;
        };
        auto le = lower_bound(begin(sa), end(sa), 0, cmp);
        auto ri = lower_bound(le, end(sa), 1, cmp);
        return {le - begin(sa), ri - begin(sa)};
    }
    /**
     * @param t needle
     * @returns min i such that t == s.substr(i, ssize(t)) or -1. For example,
     * replace RMQ with kth-smallest PST/Wavelet to solve
     * https://open.kattis.com/problems /anothersubstringqueryproblem
     * @time O(|t| * log(|s|))
     * @space O(1)
     */
    int find_first(const T& t) const {
        auto [le, ri] = find(t);
        if (le == ri) return -1;
        return rmq_sa.query(le, ri);
    }
};
