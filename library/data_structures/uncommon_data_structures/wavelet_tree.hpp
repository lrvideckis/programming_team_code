/** @file */
#pragma once
struct bit_presum {
    int n;
    vector<uint64_t> mask;
    vector<int> presum;
    bit_presum(const vector<bool>& arr) : n(ssize(arr)), mask((n + 63) / 64 + 1), presum(ssize(mask)) {
        for (int i = 0; i < n; i++)
            mask[i >> 6] |= (uint64_t(arr[i]) << (i & 63));
        for (int i = 0; i < ssize(mask) - 1; i++)
            presum[i + 1] = __builtin_popcountll(mask[i]) + presum[i];
    }
    // 0 <= idx < i
    inline int popcount(int i) const {
        assert(0 <= i && i <= n);
        return presum[i >> 6] + __builtin_popcountll(mask[i >> 6] & ((1ULL << (i & 63)) - 1));
    }
};

inline int split(int tl, int tr) {
    int pw2 = 1 << __lg(tr - tl);
    return min(tl + pw2, tr - pw2 / 2);
}

struct wavelet_tree {
    const int N, MINV, MAXV;

    vector<bit_presum> tree;
    vector<vector<long long>> tree_pref;

    wavelet_tree(vector<int> arr, int minv, int maxv) : N(ssize(arr)), MINV(minv), MAXV(maxv), tree(MAXV - MINV, vector<bool>()), tree_pref(MAXV - MINV) {
        for (int val : arr) assert(MINV <= val && val < MAXV); //TODO: should I keep this?
        build(arr, 0, N, MINV, MAXV, 1);
    }

    void build(vector<int>& arr, int le, int ri, int tl, int tr, int v) {
        if (tr - tl <= 1) return;
        int tm = split(tl, tr);
        auto low = [&](int val) -> bool {return val < tm;};
        vector<bool> bits(ri - le);
        transform(begin(arr) + le, begin(arr) + ri, begin(bits), low);
        tree[v] = bit_presum(bits);
        tree_pref[v].resize(ri - le + 1);
        inclusive_scan(begin(arr) + le, begin(arr) + ri, begin(tree_pref[v]) + 1, plus<long long>(), 0LL);
        int mi = int(stable_partition(begin(arr) + le, begin(arr) + ri, low) - begin(arr));
        build(arr, le, mi, tl, tm, 2 * v);
        build(arr, mi, ri, tm, tr, 2 * v + 1);
    }

    //count idx s.t. le <= idx < ri and x <= arr[idx] < y
    int rect_count(int le, int ri, int x, int y) const {
        assert(0 <= le && le <= ri && ri <= N);
        assert(MINV <= x && x <= y && y <= MAXV);
        return rect_count(le, ri, x, y, MINV, MAXV, 1);
    }
    int rect_count(int le, int ri, int x, int y, int tl, int tr, int v) const {
        if (y <= tl || tr <= x) return 0;
        if (x <= tl && tr <= y) return ri - le;
        int tm = split(tl, tr), pl = tree[v].popcount(le), pr = tree[v].popcount(ri);
        return rect_count(pl, pr, x, y, tl, tm, 2 * v) +
               rect_count(le - pl, ri - pr, x, y, tm, tr, 2 * v + 1);
    }

    //sum of arr[idx] s.t. le <= idx < ri and x <= arr[idx] < y
    long long rect_sum(int le, int ri, int x, int y) const {
        assert(0 <= le && le <= ri && ri <= N);
        assert(MINV <= x && x <= y && y <= MAXV);
        return rect_sum(le, ri, x, y, MINV, MAXV, 1);
    }
    long long rect_sum(int le, int ri, int x, int y, int tl, int tr, int v) const {
        if (y <= tl || tr <= x) return 0;
        if (x <= tl && tr <= y) return (tr - tl == 1 ? 1LL * tl * (ri - le) : tree_pref[v][ri] - tree_pref[v][le]);
        int tm = split(tl, tr), pl = tree[v].popcount(le), pr = tree[v].popcount(ri);
        return rect_sum(pl, pr, x, y, tl, tm, 2 * v) +
               rect_sum(le - pl, ri - pr, x, y, tm, tr, 2 * v + 1);
    }

    int kth_smallest(int le, int ri, int k) const {
        assert(0 <= le && ri <= N);
        assert(1 <= k && k <= ri - le);
        return kth_smallest(le, ri, k, MINV, MAXV, 1);
    }
    int kth_smallest(int le, int ri, int k, int tl, int tr, int v) const {
        if (tr - tl == 1) return tl;
        int tm = split(tl, tr), pl = tree[v].popcount(le), pr = tree[v].popcount(ri);
        if (k <= pr - pl) return kth_smallest(pl, pr, k, tl, tm, 2 * v);
        return kth_smallest(le - pl, ri - pr, k - (pr - pl), tm, tr, 2 * v + 1);
    }

    long long kth_sum(int le, int ri, int k) const {
        assert(0 <= le && ri <= N);
        assert(0 <= k && k <= ri - le);
        return kth_sum(le, ri, k, MINV, MAXV, 1);
    }
    long long kth_sum(int le, int ri, int k, int tl, int tr, int v) const {
        if (tr - tl == 1) return 1LL * k * tl;
        int tm = split(tl, tr), pl = tree[v].popcount(le), pr = tree[v].popcount(ri);
        if (k <= pr - pl) return kth_sum(pl, pr, k, tl, tm, 2 * v);
        long long sum_left = (tm - tl == 1 ? 1LL * tl * (pr - pl) : tree_pref[2 * v][pr] - tree_pref[2 * v][pl]);
        return sum_left + kth_sum(le - pl, ri - pr, k - (pr - pl), tm, tr, 2 * v + 1);
    }
};
