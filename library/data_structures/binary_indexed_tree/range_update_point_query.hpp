/** @file */
#pragma once
#include "binary_indexed_tree.hpp"
template <class T> struct bit_inv {
    int n;
    BIT<T> bit;
    bit_inv(int a_n) : n(a_n), bit(n) {}
    bit_inv(const vector<T>& a) : n(ssize(a)) {
        vector<T> init(n);
        adjacent_difference(begin(a), end(a), begin(init));
        bit = BIT<T>(init);
    }
    inline void update(int le, int ri, const T& d) {
        assert(0 <= le && le <= ri && ri <= n);
        bit.update(le, d);
        if (ri < n) bit.update(ri, -d);
    }
    inline T get_index(int i) const {
        assert(0 <= i && i < n);
        return bit.sum(i + 1);
    }
};
