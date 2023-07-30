/** @file */
#pragma once
#include "binary_indexed_tree.hpp"
/**
 * @see https://stackoverflow.com/a/27877427/18306912
 *
 * range update, range query
 */
template <class T> struct bit_rurq {
    int n;
    BIT<T> bit1, bit2;
    /**
     * @param a_n size
     * @time O(n)
     * @space O(n) for both bits
     */
    bit_rurq(int a_n) : n(a_n), bit1(n), bit2(n) {}
    /**
     * @param a initial array
     * @time O(n)
     * @space O(n) for both bits
     */
    bit_rurq(const vector<T>& a) : n(ssize(a)) {
        vector<T> init(n);
        adjacent_difference(begin(a), end(a), begin(init));
        bit1 = BIT<T>(init);
        for (int i = 0; i < n; i++) init[i] *= i;
        bit2 = BIT<T>(init);
    }
    /**
     * does a[le] += d, a[le + 1] += d, ..., a[ri - 1] += d
     *
     * @param le,ri defines range [le, ri)
     * @param d delta to add to each index in range
     * @time O(log n)
     * @space O(1)
     */
    inline void update(int le, int ri, T d) {
        assert(0 <= le && le <= ri && ri <= n);
        bit1.update(le, d);
        bit2.update(le, le * d);
        if (ri < n) {
            bit1.update(ri, -d);
            bit2.update(ri, -ri * d);
        }
    }
    /**
     * @param ri defines range [0, ri)
     * @returns a[0] + a[1] + ... + a[ri - 1]
     * @time O(log n)
     * @space O(1)
     */
    inline T sum(int ri) const {
        assert(0 <= ri && ri <= n);
        return bit1.sum(ri) * ri - bit2.sum(ri);
    }
    /**
     * @param le,ri defines range [le, ri)
     * @returns a[le] + a[le + 1] + ... + a[ri - 1]
     * @time O(log n)
     * @space O(1)
     */
    inline T sum(int le, int ri) const {
        assert(le <= ri);
        return sum(ri) - sum(le);
    }
};
