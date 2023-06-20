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
    int N;//TODO make const again
    vector<uint64_t> mask;
    vector<int> presum;

    bit_presum() : N(0) {}//TODO: remove this?
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

//TODO rearrange params to match other seg trees
//TODO rename params to le, ri
//TODO test which midpoint gives least memory/is fastest
struct wavelet_tree {
    const int N, MINN, MAXN;

    vector<bit_presum> tree;

    wavelet_tree(vector<int> arr) : N(ssize(arr)), MINN(*min_element(begin(arr), end(arr))), MAXN(*max_element(begin(arr), end(arr)) + 1), tree(4*(MAXN-MINN)) {
        arr.reserve(2 * ssize(arr));//so that stable_partition is O(n)
        build(arr, 0, N, 1, MINN, MAXN);
    }

    void build(vector<int>& arr, int b, int e, int p, int l, int r) {
        assert(p < ssize(tree));
        int m = l + (r-l)/2;
        auto low = [&](int val) -> bool {return val < m;};
        vector<bool> bits(e-b);
        transform(begin(arr) + b, begin(arr) + e, begin(bits), low);
        {
            bit_presum curr(bits);
            //TODO: this is terrible, I want to do tree[p] = bit_presum(bits);
            tree[p].N = curr.N;
            tree[p].mask = curr.mask;
            tree[p].presum = curr.presum;
        }
        if (r-l == 1) return;
        int m2 = stable_partition(begin(arr)+b, begin(arr)+e, low) - begin(arr);
        build(arr, b, m2, 2*p, l, m);
        build(arr, m2, e, 2*p+1, m, r);
    }

    //kth(i,j,0) returns min of range [i,j)
    int kth(int i, int j, int k) const {
        return kth(i, j, k, 1, MINN, MAXN);
    }
    int kth(int i, int j, int k, int p, int l, int r) const {
        if (r-l == 1) return l;
        assert(p < ssize(tree));
        int m = l+(r-l)/2, ei = tree[p].popcount(i), ej = tree[p].popcount(j);
        if (k < ej-ei) return kth(ei, ej, k, 2*p, l, m);
        return kth(i-ei, j-ej, k-(ej-ei), 2*p+1, m, r);
    }
};
