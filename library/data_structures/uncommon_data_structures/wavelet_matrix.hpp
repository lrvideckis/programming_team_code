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

class Bit_Presum{
public:
    static constexpr uint32_t omega = CHAR_BIT * sizeof(uint64_t);
    static constexpr uint32_t lg_omega = __lg(omega);
    static_assert(omega == 64u);

    Bit_Presum(vector<uint64_t> mask_) : n(mask_.size()), mask(move(mask_)), presum(n+1){
        build();
    }
    Bit_Presum(uint32_t bits, bool init_val = 0) : n((bits>>lg_omega) + 1), mask(n, init_val ? ~uint64_t{0} : uint64_t{0}), presum(n+1){
        if(init_val) mask.back()<<=((n<<lg_omega) - bits);
        build();
    }
    /// popcount l <= i < r
    uint32_t query(uint32_t l, uint32_t r) const {
        if(__builtin_expect(r < l, false)) return 0;
        return query(r) - query(l);
    }
    /// popcount 0 <= i < x
    uint32_t query(uint32_t x) const {
        uint32_t high = x>>lg_omega, low = x & ((uint64_t{1}<<lg_omega) - 1);
        uint32_t ret = presum_query(high);
        ret+= __builtin_popcountll(mask[high]& ((uint64_t{1} << low)-1));
        return ret;
    }

    void update_pre_build(uint32_t x, bool val){
        uint32_t high = x>>lg_omega, low = x & ((1u<<lg_omega) - 1);
        mask[high] = (mask[high] & ~(uint64_t{1} << low)) | (uint64_t{val}<<low);
    }


private:
    void presum_build(){
        for(uint32_t x=1;x<=n;++x){
            presum[x]+=presum[x-1];
        }
    }
    // sum 0 <= i < x
    uint32_t presum_query(uint32_t x) const {
        return presum[x];
    }
    void build(){
        for(uint32_t x=0;x<n;++x){
            presum[x+1] = __builtin_popcountll(mask[x]);
        }
        presum_build();
    }

    const uint32_t n;
    vector<uint64_t> mask;
    vector<uint32_t> presum;
};
