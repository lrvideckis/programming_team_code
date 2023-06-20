/*
 * not pointer based
 * 32/64x memory optimized
 * supports operations:
 *   - kth smallest
 *   - count < val seems pointless
 *   - count = val seems pointless
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
    inline int popcount(int i) const {
        assert(0 <= i && i <= n);
        return presum[i>>6] + __builtin_popcountll(mask[i>>6] & ((1ULL << (i & 63))-1));
    }
};

inline int split(int tl, int tr) {
    int pw2 = 1 << __lg(tr - tl);
    return min(tl + pw2, tr - pw2 / 2);
}

//TODO figure out which debug flag makes this test TLE
struct wavelet_tree {
    const int N, MINV, MAXV;

    vector<bit_presum> tree;

    wavelet_tree(vector<int> arr, int minv, int maxv) : N(ssize(arr)), MINV(minv), MAXV(maxv), tree(2*(MAXV-MINV), vector<bool>()) {
        for(int val : arr) assert(MINV <= val && val < MAXV);//TODO: should I keep this?
        arr.reserve(2 * ssize(arr));//so that stable_partition is O(n)
        if(arr.empty()) return;//TODO: find better way to handle empty array
        build(arr, 0, N, MINV, MAXV, 1);
    }

    void build(vector<int>& arr, int le, int ri, int tl, int tr, int v) {
        int tm = split(tl,tr);
        auto low = [&](int val) -> bool {return val < tm;};
        vector<bool> bits(ri-le);
        transform(begin(arr) + le, begin(arr) + ri, begin(bits), low);
        tree[v] = bit_presum(bits);
        if (tr-tl == 1) return;
        int mi = stable_partition(begin(arr)+le, begin(arr)+ri, low) - begin(arr);
        build(arr, le, mi, tl, tm, 2*v);
        build(arr, mi, ri, tm, tr, 2*v+1);
    }

    //count idx s.t. le <= idx < ri and x <= arr[idx] < y
    int count(int le, int ri, int x, int y) {
        assert(0 <= le && le <= ri && ri <= N);
        assert(MINV <= x && x <= y && y <= MAXV);
        return count(le,ri,x,y,MINV, MAXV, 1);
    }
    int count(int le, int ri, int x, int y, int tl, int tr, int v) {
        if (y <= tl || tr <= x) return 0;
        if (x <= tl && tr <= y) return ri-le;
        int tm = split(tl,tr), pl = tree[v].popcount(le), pr = tree[v].popcount(ri);
        return count(pl, pr, x, y, tl, tm, 2*v) +
            count(le-pl, ri-pr, x, y, tm, tr, 2*v+1);
    }

    //kth(le,ri,0) returns min of range [le,ri)
    int kth(int le, int ri, int k) const {
        assert(0 <= le && ri <= N);
        assert(0 <= k && k < ri - le);
        return kth(le, ri, k, MINV, MAXV, 1);
    }
    int kth(int le, int ri, int k, int tl, int tr, int v) const {
        if (tr-tl == 1) return tl;
        int tm = split(tl,tr), pl = tree[v].popcount(le), pr = tree[v].popcount(ri);
        if (k < pr-pl) return kth(pl, pr, k, tl, tm, 2*v);
        return kth(le-pl, ri-pr, k-(pr-pl), tm, tr, 2*v+1);
    }
};
