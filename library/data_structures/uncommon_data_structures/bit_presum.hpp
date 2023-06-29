/** @file */
#pragma once
/**
 * @see https://github.com/dacin21/dacin21_codebook /blob/master/trees/wavelet_matrix.cpp
 *
 * space efficient boolean array with prefix sum query
 */
struct bit_presum {
    int n;
    vector<uint64_t> mask;
    vector<int> presum;
    /**
     * @param arr boolean array
     * @time O(n)
     * @space O(n / 64)
     */
    bit_presum(const vector<bool>& arr) : n(ssize(arr)), mask(n / 64 + 1), presum(ssize(mask)) {
        for (int i = 0; i < n; i++)
            mask[i >> 6] |= (uint64_t(arr[i]) << (i & 63));
        for (int i = 0; i < ssize(mask) - 1; i++)
            presum[i + 1] = __builtin_popcountll(mask[i]) + presum[i];
    }
    /**
     * @param i defines range [0, i)
     * @returns sum/popcount of range
     * @time O(1)
     * @space O(1)
     */
    inline int popcount(int i) const {
        assert(0 <= i && i <= n);
        return presum[i >> 6] + __builtin_popcountll(mask[i >> 6] & ((1ULL << (i & 63)) - 1));
    }
    /**
     * @param i index
     * @returns 1 iff arr[i] was on
     * @time O(1)
     * @space O(1)
     */
    inline bool on(int i) const {
        assert(0 <= i && i < n);
        return (mask[i >> 6] >> (i & 63)) & 1;
    }
};
