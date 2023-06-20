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
    int n;
    vector<uint64_t> mask;
    vector<int> presum;
    bit_presum(const vector<bool>& arr) : n(ssize(arr)), mask((n+63) / 64 + 1), presum(ssize(mask)) {
        for(int i = 0; i < n; i++)
            mask[i >> 6] |= (uint64_t(arr[i]) << (i & 63));
        for(int i = 0; i < ssize(mask)-1; i++)
            presum[i+1] = __builtin_popcountll(mask[i]) + presum[i];
    }
    // 0 <= idx < i
    int popcount(int i) const {
        assert(0 <= i && i <= n);
        return presum[i>>6] + __builtin_popcountll(mask[i>>6] & ((1ULL << (i & 63))-1));
    }
};

inline int split(int tl, int tr) {
    int pw2 = 1 << __lg(tr - tl);
    return min(tl + pw2, tr - pw2 / 2);
}

//TODO rearrange params to match other seg trees
//TODO rename params to le, ri
//TODO which functions to make inline
//TODO figure out which debug flag makes this test TLE
struct wavelet_tree {
    const int N, MINV, MAXV;

    vector<bit_presum> tree;

    wavelet_tree(vector<int> arr, int minv, int maxv) : N(ssize(arr)), MINV(minv), MAXV(maxv), tree(2*(MAXV-MINV), vector<bool>()) {
        for(int val : arr) assert(MINV <= val && val < MAXV);//TODO: should I keep this?
        arr.reserve(2 * ssize(arr));//so that stable_partition is O(n)
        build(arr, 0, N, 1, MINV, MAXV);
    }

    void build(vector<int>& arr, int b, int e, int p, int l, int r) {
        int m = split(l,r);
        auto low = [&](int val) -> bool {return val < m;};
        vector<bool> bits(e-b);
        transform(begin(arr) + b, begin(arr) + e, begin(bits), low);
        tree[p] = bit_presum(bits);
        if (r-l == 1) return;
        int m2 = stable_partition(begin(arr)+b, begin(arr)+e, low) - begin(arr);
        build(arr, b, m2, 2*p, l, m);
        build(arr, m2, e, 2*p+1, m, r);
    }

    //kth(i,j,0) returns min of range [i,j)
    int kth(int i, int j, int k) const {
        //TODO: add asserts cleaning params
        return kth(i, j, k, 1, MINV, MAXV);
    }
    int kth(int i, int j, int k, int p, int l, int r) const {
        if (r-l == 1) return l;
        int m = split(l,r), ei = tree[p].popcount(i), ej = tree[p].popcount(j);
        if (k < ej-ei) return kth(ei, ej, k, 2*p, l, m);
        return kth(i-ei, j-ej, k-(ej-ei), 2*p+1, m, r);
    }
};
