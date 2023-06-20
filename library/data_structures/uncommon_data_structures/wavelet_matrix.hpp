/*
 * not pointer based
 * 32/64x memory optimized
 * supports operations:
 *   - kth smallest
 *   - count < val
 *   - count = val
 *   - rectangle count: # vals x in subarray s.t. low <= x < high
 *   - sum of all values < val (requires n log memory which isn't 32/64x optimized)
 *         for space comment for this, mention
 *   - sum of all values in rectangle (requires n log memory which isn't 32/64x optimized)
 *   - sum of all values = val seems pointless
 * */

struct bit_presum {
    const int N;
    vector<uint64_t> mask;
    vector<int> presum;

    bit_presum(const vector<bool>& arr) : N(ssize(arr)), mask((N+63) / 64 + 1), presum(ssize(mask)) {
        for(int i = 0; i < N; i++)
            mask[i >> 6] |= (uint64_t(arr[i]) << (i & 63));
        for(int i = 0; i < ssize(mask)-1; i++)
            presum[i+1] = __builtin_popcountll(mask[i]) + presum[i];
    }

    /// l <= idx < r
    int popcount(int l, int r) const {
        assert(0 <= l && l <= r && r <= N);
        return popcount(r) - popcount(l);
    }

    /// 0 <= idx < i
    int popcount(int i) const {
        assert(0 <= i && i <= N);
        int high = i >> 6, low = i & 63;
        return presum[high] + __builtin_popcountll(mask[high] & ((1ULL << low)-1));//sanitizers may cause RTE here from overflow/underflow
    }
};
