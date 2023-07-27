/** @file */
#pragma once
#include "../../data_structures/sparse_table.hpp"
#include "manacher.hpp"
/**
 * queries for longest palindromic substring of a given substring
 */
template <class T> struct longest_pal_query {
    vector<int> man, idx;
    RMQ<int> rmq;
    /**
     * @param s string/vector
     * @time O(n log n)
     * @space O(n log n) for rmq, everything else is O(n)
     */
    longest_pal_query(const T& s) : man(manacher(s)), idx(ssize(s)) {
        iota(begin(idx), end(idx), 1);
        vector<int> init(ssize(man));
        iota(begin(init), end(init), 0);
        rmq = RMQ<int>(init, [&](int i1, int i2) -> int {return len(i1) < len(i2) ? i2 : i1;});
    }
    /**
     * @param i center
     * @returns length of longest palindrome around center
     * @time O(1)
     * @space O(1)
     */
    inline int len(int i) const {return i - 2 * man[i] + 1;}
    /**
     * approach: binary search: is there some palindromic substring with length >= mid ?
     * note for a substring [le, ri) of s, the "relevant" centers are subarray [2 * le, 2 * ri - 1) of `man`
     *
     * when center i (in "relevant" range) is even (so represents an odd-length palindrome):
     *     - i / 2 is index of middle of palindrome
     *     - le <= i / 2 < ri
     * when center i (in "relevant" range) is odd (so represents an even-length palindrome):
     *     - (i - 1) / 2, (i + 1) / 2 are indexes of middles of palindrome
     *     - le <= (i - 1) / 2 < (i + 1) / 2 < ri
     *
     * @param le,ri defines substring [le, ri) of s
     * @returns {start index, length} of longest palindromic substring of s.substr(le, ri - le)
     *     if there are multiple longest answers, this returns an arbitrary start index
     * @time O(log n)
     * @space O(1)
     */
    inline pair<int, int> longest_pal(int le, int ri) const {
        assert(0 <= le && le < ri && ri <= ssize(idx));
        int pal_len = int(lower_bound(begin(idx), begin(idx) + (ri - le), 0, [&](int mid, int) -> bool {
            return len(rmq.query(2 * le + mid - 1, 2 * ri - mid)) >= mid;
        }) - begin(idx));
        int best_center = rmq.query(2 * le + pal_len - 1, 2 * ri - pal_len);
        return {(best_center + 1 - pal_len) / 2, pal_len};
    }
};
