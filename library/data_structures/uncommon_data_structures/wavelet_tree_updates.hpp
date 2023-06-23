/** @file */
#pragma once
#include "../binary_indexed_tree.hpp"

struct bit_bit {
    int n;
    vector<uint64_t> mask;
    BIT<int> presum;
    //TODO: re-think if these size formulas are minimal
    bit_bit(int a_n) : n(a_n), mask(n / 64 + 1, -1), presum(vector<int>((n + 63) / 64, 1)) {}
    inline int popcount(int i) const {
        assert(0 <= i && i <= n);
        return presum.sum(i >> 6) + __builtin_popcountll(mask[i >> 6] & ((1ULL << (i & 63)) - 1));
    }
    void set(int i, bool new_val) {
        int high = i >> 6, low = i & 63;
        if(((mask[high] >> low) & 1) != new_val) {
            mask[high] ^= 1ULL << low;
            presum.update(high, new_val ? 1 : -1);
        }
    }
};
struct bit_presum {
    int n;
    vector<uint64_t> mask;
    vector<int> presum;
    bit_presum(const vector<bool>& arr) : n(ssize(arr)), mask(n / 64 + 1), presum(ssize(mask)) {
        for (int i = 0; i < n; i++)
            mask[i >> 6] |= (uint64_t(arr[i]) << (i & 63));
        for (int i = 0; i < ssize(mask) - 1; i++)
            presum[i + 1] = __builtin_popcountll(mask[i]) + presum[i];
    }
    inline int popcount(int i) const {
        assert(0 <= i && i <= n);
        return presum[i >> 6] + __builtin_popcountll(mask[i >> 6] & ((1ULL << (i & 63)) - 1));
    }
};
//TODO: write tests
inline int split(int tl, int tr) {
    int pw2 = 1 << __lg(tr - tl);
    return min(tl + pw2, tr - pw2 / 2);
}
struct wavelet_tree_updates {
    const int N, MINV, MAXV;
    vector<bit_presum> tree;
    vector<bit_bit> tree_bit;//TODO: better name?
    wavelet_tree_updates(vector<int> arr, int minv, int maxv) : N(ssize(arr)), MINV(minv), MAXV(maxv), tree(MAXV - MINV, vector<bool>()), tree_bit(MAXV - MINV, 0) {
        build(arr, 0, N, MINV, MAXV, 1);
    }
    void build(vector<int>& arr, int le, int ri, int tl, int tr, int v) {
        if (tr - tl <= 1) return;
        int tm = split(tl, tr);
        auto low = [&](int val) -> bool {return val < tm;};
        vector<bool> bits(ri - le);
        transform(begin(arr) + le, begin(arr) + ri, begin(bits), low);
        tree[v] = bit_presum(bits);
        tree_bit[v] = bit_bit(ri - le);
        int mi = int(stable_partition(begin(arr) + le, begin(arr) + ri, low) - begin(arr));
        build(arr, le, mi, tl, tm, 2 * v);
        build(arr, mi, ri, tm, tr, 2 * v + 1);
    }
    void set_active(int idx, bool is_active) {
        assert(0 <= idx && idx < N);
        //set_impl(idx, MINV, MAXV, 1);
    }
    /*
    void set_impl(int idx, int tl, int tr, int v) const {
        if (tr - tl == 1) return;
        int tm = split(tl, tr), pi = tree[v].sum(idx);
        if () return set_impl(pi, tl, tm, 2 * v);
        set_impl(idx - pi, tm, tr, 2 * v + 1);
    }
    */
    int rect_count(int le, int ri, int x, int y) const {
        assert(0 <= le && le <= ri && ri <= N && x <= y);
        return rect_count_impl(le, ri, x, y, MINV, MAXV, 1);
    }
    int rect_count_impl(int le, int ri, int x, int y, int tl, int tr, int v) const {
        if (y <= tl || tr <= x) return 0;
        if (x <= tl && tr <= y) return ri - le;
        int tm = split(tl, tr), pl = tree[v].popcount(le), pr = tree[v].popcount(ri);
        return rect_count_impl(pl, pr, x, y, tl, tm, 2 * v) +
               rect_count_impl(le - pl, ri - pr, x, y, tm, tr, 2 * v + 1);
    }
    int kth_smallest(int le, int ri, int k) const {
        assert(0 <= le && ri <= N);
        assert(1 <= k && k <= ri - le);
        return kth_smallest_impl(le, ri, k, MINV, MAXV, 1);
    }
    int kth_smallest_impl(int le, int ri, int k, int tl, int tr, int v) const {
        if (tr - tl == 1) return tl;
        int tm = split(tl, tr), pl = tree[v].popcount(le), pr = tree[v].popcount(ri);
        if (k <= pr - pl) return kth_smallest_impl(pl, pr, k, tl, tm, 2 * v);
        return kth_smallest_impl(le - pl, ri - pr, k - (pr - pl), tm, tr, 2 * v + 1);
    }
};
