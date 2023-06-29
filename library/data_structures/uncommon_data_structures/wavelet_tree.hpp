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
/**
 * @see https://codeforces.com/blog/entry/112755
 * @param tl,tr defines range [tl, tr)
 * @returns split point of range which makes the wavelet tree a complete
 * binary tree
 */
inline int split(int tl, int tr) {
    int pw2 = 1 << __lg(tr - tl);
    return min(tl + pw2, tr - pw2 / 2);
}
/**
 * @see https://ioinformatics.org/journal/v10_2016_19_37.pdf
 * https://github.com/brunomaletta/Biblioteca /blob/master/Codigo/Estruturas/waveletTree.cpp
 */
struct wavelet_tree {
    const int N, MINV, MAXV;
    vector<bit_presum> bit_presums;
    vector<vector<long long>> presums;
    /**
     * @param arr,minv,maxv must satisfy minv <= arr[i] < maxv
     * @time O((maxv - minv) + n * log(maxv - minv))
     * @space O((maxv - minv) + n * log(maxv - minv) / 64) for `bit_presums`
     *        O((maxv - minv) + n * log(maxv - minv))      for `presums`
     */
    wavelet_tree(vector<int> arr, int minv, int maxv) : N(ssize(arr)), MINV(minv), MAXV(maxv), bit_presums(MAXV - MINV, vector<bool>()), presums(MAXV - MINV) {
        build(arr, 0, N, MINV, MAXV, 1);
    }
    void build(vector<int>& arr, int le, int ri, int tl, int tr, int v) {
        if (tr - tl <= 1) return;
        int tm = split(tl, tr);
        auto low = [&](int val) -> bool {return val < tm;};
        vector<bool> bits(ri - le);
        transform(begin(arr) + le, begin(arr) + ri, begin(bits), low);
        bit_presums[v] = bit_presum(bits);
        presums[v].resize(ri - le + 1);
        inclusive_scan(begin(arr) + le, begin(arr) + ri, begin(presums[v]) + 1, plus<long long>(), 0LL);
        int mi = int(stable_partition(begin(arr) + le, begin(arr) + ri, low) - begin(arr));
        build(arr, le, mi, tl, tm, 2 * v);
        build(arr, mi, ri, tm, tr, 2 * v + 1);
    }
    /**
     * @param le,ri,x,y defines rectangle: indexes in [le, ri), values in [x, y)
     * @returns number of indexes i such that le <= i < ri and x <= arr[i] < y
     * @time O(log(maxv - minv))
     * @space O(log(maxv - minv)) for recursive stack
     */
    int rect_count(int le, int ri, int x, int y) const {
        assert(0 <= le && le <= ri && ri <= N && x <= y);
        return rect_count_impl(le, ri, x, y, MINV, MAXV, 1);
    }
    int rect_count_impl(int le, int ri, int x, int y, int tl, int tr, int v) const {
        if (y <= tl || tr <= x) return 0;
        if (x <= tl && tr <= y) return ri - le;
        int tm = split(tl, tr), pl = bit_presums[v].popcount(le), pr = bit_presums[v].popcount(ri);
        return rect_count_impl(pl, pr, x, y, tl, tm, 2 * v) +
               rect_count_impl(le - pl, ri - pr, x, y, tm, tr, 2 * v + 1);
    }
    /**
     * @param le,ri,x,y defines rectangle: indexes in [le, ri), values in [x, y)
     * @returns sum of values arr[i] such that le <= i < ri and x <= arr[i] < y
     * @time O(log(maxv - minv))
     * @space O(log(maxv - minv)) for recursive stack
     */
    long long rect_sum(int le, int ri, int x, int y) const {
        assert(0 <= le && le <= ri && ri <= N && x <= y);
        return rect_sum_impl(le, ri, x, y, MINV, MAXV, 1);
    }
    long long rect_sum_impl(int le, int ri, int x, int y, int tl, int tr, int v) const {
        if (y <= tl || tr <= x) return 0;
        if (x <= tl && tr <= y) return (tr - tl == 1 ? 1LL * tl * (ri - le) : presums[v][ri] - presums[v][le]);
        int tm = split(tl, tr), pl = bit_presums[v].popcount(le), pr = bit_presums[v].popcount(ri);
        return rect_sum_impl(pl, pr, x, y, tl, tm, 2 * v) +
               rect_sum_impl(le - pl, ri - pr, x, y, tm, tr, 2 * v + 1);
    }
    /**
     * @param le,ri defines range [le, ri)
     * @param k must satisfy 1 <= k <= ri - le
     * @returns kth smallest number in range.
     *     - kth_smallest(le,ri,1) returns the min
     *     - kth_smallest(le,ri,(ri-le)) returns the max
     * @time O(log(maxv - minv))
     * @space O(log(maxv - minv)) for recursive stack
     */
    int kth_smallest(int le, int ri, int k) const {
        assert(0 <= le && ri <= N);
        assert(1 <= k && k <= ri - le);
        return kth_smallest_impl(le, ri, k, MINV, MAXV, 1);
    }
    int kth_smallest_impl(int le, int ri, int k, int tl, int tr, int v) const {
        if (tr - tl == 1) return tl;
        int tm = split(tl, tr), pl = bit_presums[v].popcount(le), pr = bit_presums[v].popcount(ri);
        if (k <= pr - pl) return kth_smallest_impl(pl, pr, k, tl, tm, 2 * v);
        return kth_smallest_impl(le - pl, ri - pr, k - (pr - pl), tm, tr, 2 * v + 1);
    }
    /**
     * @param le,ri defines range [le, ri)
     * @param k must satisfy 0 <= k <= ri - le
     * @returns the sum of the k smallest numbers in range.
     *     - kth_sum(le,ri,0) returns 0
     *     - kth_sum(le,ri,1) returns the min
     *     - kth_sum(le,ri,(ri-le)) returns the sum
     * @time O(log(maxv - minv))
     * @space O(log(maxv - minv)) for recursive stack
     */
    long long kth_sum(int le, int ri, int k) const {
        assert(0 <= le && ri <= N);
        assert(0 <= k && k <= ri - le);
        return kth_sum_impl(le, ri, k, MINV, MAXV, 1);
    }
    long long kth_sum_impl(int le, int ri, int k, int tl, int tr, int v) const {
        if (tr - tl == 1) return 1LL * k * tl;
        int tm = split(tl, tr), pl = bit_presums[v].popcount(le), pr = bit_presums[v].popcount(ri);
        if (k <= pr - pl) return kth_sum_impl(pl, pr, k, tl, tm, 2 * v);
        long long sum_left = (tm - tl == 1 ? 1LL * tl * (pr - pl) : presums[2 * v][pr] - presums[2 * v][pl]);
        return sum_left + kth_sum_impl(le - pl, ri - pr, k - (pr - pl), tm, tr, 2 * v + 1);
    }
};
