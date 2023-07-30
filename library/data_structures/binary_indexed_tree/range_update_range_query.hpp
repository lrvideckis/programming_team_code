/** @file */
#pragma once
#include "binary_indexed_tree.hpp"
/**
 * range update, range query
 */
template <class T> struct bit_rurq {
    int n;
    BIT<T> bit1, bit2;
    bit_rurq(int a_n) : n(a_n), bit1(n), bit2(n) {}
    bit_rurq(const vector<T>& a) : n(ssize(a)) {
        vector<T> init(n);
        adjacent_difference(begin(a), end(a), begin(init));
        bit1 = BIT<T>(init);

    }
    inline void update(int le, int ri, const T& d) {
        assert(0 <= le && le <= ri && ri <= n);
        bit1.update(le, d);
        bit2.update(le, le * d);
        if (ri < n) {
            bit1.update(ri, -d);
            bit2.update(ri, -ri * d);
        }
    }
    inline T sum(int ri) const {
        assert(0 <= ri && ri <= n);
        return bit1.sum(ri) * ri - bit2.sum(ri);
    }
    inline T sum(int le, int ri) const {
        assert(le <= ri);
        return sum(ri) - sum(le);
    }
};
