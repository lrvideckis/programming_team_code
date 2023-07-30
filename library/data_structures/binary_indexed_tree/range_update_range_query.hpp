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
    /*
    bit_inv(const vector<T>& a) : n(ssize(a)) {
        vector<T> init(n);
        adjacent_difference(begin(a), end(a), begin(init));
        bit = BIT<T>(init);
    }
    */
    inline void update(int le, int ri, const T& d) {
        assert(0 <= le && le <= ri && ri <= n);
        bit1.update(le, d);
        bit2.update(le, (le - 1) * d);
        if (ri < n) {
            bit1.update(ri, -d);
            bit2.update(ri, -(ri - 1)*d);
        }
    }
    inline T sum(int ri) const {
        //assert(0 <= ri && ri <= n);
        return bit1.sum(ri + 1) * ri - bit2.sum(ri + 1);
    }
    inline T sum(int le, int ri) const {
        ri--;
        //assert(le <= ri);
        T res = sum(ri);
        if (le) res -= sum(le - 1);
        return res;
    }
};
