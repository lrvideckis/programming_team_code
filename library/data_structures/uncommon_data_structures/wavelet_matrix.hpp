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

struct wavelet_matrix {
    const int N, MINN, MAXN;

    vector<int> esq[4*(MAXN-MINN)];

    wavelet_matrix(const vector<int>& arr) : N(ssize(arr)), MINN(*min_element(begin(arr), end(arr))), MAXN(*max_element(begin(arr), end(arr)) + 1) {
        build(0, n, 1, MINN, MAXN);
    }
    void build(int b = 0, int e = n, int p = 1, int l = MINN, int r = MAXN) {
        int m = (l+r)/2; esq[p].push_back(0); pref[p].push_back(0);
        for (int i = b; i < e; i++) {
            esq[p].push_back(esq[p].back()+(v[i]<=m));
            pref[p].push_back(pref[p].back()+v[i]);
        }
        if (l == r) return;
        int m2 = stable_partition(v+b, v+e, [=](int i){return i <= m;}) - v;
        build(b, m2, 2*p, l, m), build(m2, e, 2*p+1, m+1, r);
    }

    int count(int i, int j, int x, int y, int p = 1, int l = MINN, int r = MAXN) const {
        if (y < l || r < x) return 0;
        if (x <= l && r <= y) return j-i;
        int m = (l+r)/2, ei = esq[p][i], ej = esq[p][j];
        return count(ei, ej, x, y, 2*p, l, m)+count(i-ei, j-ej, x, y, 2*p+1, m+1, r);
    }

    int kth(int i, int j, int k, int p=1, int l = MINN, int r = MAXN) const {
        if (l == r) return l;
        int m = (l+r)/2, ei = esq[p][i], ej = esq[p][j];
        if (k <= ej-ei) return kth(ei, ej, k, 2*p, l, m);
        return kth(i-ei, j-ej, k-(ej-ei), 2*p+1, m+1, r);
    }

    int sum(int i, int j, int x, int y, int p = 1, int l = MINN, int r = MAXN) const {
        if (y < l || r < x) return 0;
        if (x <= l && r <= y) return pref[p][j]-pref[p][i];
        int m = (l+r)/2, ei = esq[p][i], ej = esq[p][j];
        return sum(ei, ej, x, y, 2*p, l, m) + sum(i-ei, j-ej, x, y, 2*p+1, m+1, r);
    }
}
