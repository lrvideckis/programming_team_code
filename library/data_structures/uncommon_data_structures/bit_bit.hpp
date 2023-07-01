#pragma once
#include "../binary_indexed_tree.hpp"
/**
 * @see https://github.com/dacin21/dacin21_codebook /blob/master/trees/wavelet_matrix_updates.cpp
 *
 * space efficient boolean array with range sum query, and point update
 */
struct bit_bit {
    int n;
    vector<uint64_t> mask;
    BIT<int> presum;
    /**
     * initially everything is on
     * @param a_n size
     * @time O(n)
     * @space O(n / 64)
     */
    bit_bit(int a_n) : n(a_n), mask(n / 64 + 1, -1), presum(vector<int>((n + 63) / 64, 64)) {}
    /**
     * @param i defines range [0, i)
     * @returns sum/popcount of range
     * @time O(log(n / 64))
     * @space O(1)
     */
    inline int popcount(int i) const {
        assert(0 <= i && i <= n);
        return presum.sum(i >> 6) + __builtin_popcountll(mask[i >> 6] & ((1ULL << (i & 63)) - 1));
    }
    /**
     * @param le,ri defines range [le, ri)
     * @returns sum/popcount of range
     * @time O(log(n / 64))
     * @space O(1)
     */
    inline int popcount(int le, int ri) const {
        assert(le <= ri);
        return popcount(ri) - popcount(le);
    }
    /**
     * @param i index
     * @returns 1 iff index i is active
     * @time O(1)
     * @space O(1)
     */
    inline bool on(int i) const {
        assert(0 <= i && i < n);
        return (mask[i >> 6] >> (i & 63)) & 1;
    }
    /**
     * @param i index
     * @param new_val we want to set arr[i] = new_val
     * @time O(log(n / 64))
     * @space O(1)
     */
    void set(int i, bool new_val) {
        assert(0 <= i && i < n);
        if (on(i) != new_val) {
            mask[i >> 6] ^= 1ULL << (i & 63);
            presum.update(i >> 6, new_val ? 1 : -1);
        }
    }
};
