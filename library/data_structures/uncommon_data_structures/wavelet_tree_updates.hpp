/** @file */
#pragma once
#include "../binary_indexed_tree.hpp"
//for bit_presum and split
#include "wavelet_tree.hpp"

//TODO: test on https://judge.yosupo.jp/problem/point_add_range_sum
/**
 * @see https://github.com/dacin21/dacin21_codebook/blob/master/trees/wavelet_matrix_updates.cpp
 */
struct bit_bit {
    int n;
    vector<uint64_t> mask;
    BIT<int> presum;
    //TODO: re-think if these size formulas are minimal
    bit_bit(int a_n) : n(a_n), mask(n / 64 + 1, -1), presum(vector<int>((n + 63) / 64, 64)) {}
    inline int popcount(int i) const {
        assert(0 <= i && i <= n);
        return presum.sum(i >> 6) + __builtin_popcountll(mask[i >> 6] & ((1ULL << (i & 63)) - 1));
    }
    inline int popcount(int le, int ri) const {
        assert(le <= ri);
        return popcount(ri) - popcount(le);
    }
    void set(int i, bool new_val) {
        assert(0 <= i && i < n);
        int high = i >> 6, low = i & 63;
        if(((mask[high] >> low) & 1) != new_val) {
            mask[high] ^= 1ULL << low;
            presum.update(high, new_val ? 1 : -1);
        }
    }
};
/**
 * @see https://ioinformatics.org/journal/v10_2016_19_37.pdf
 * https://github.com/brunomaletta/Biblioteca /blob/master/Codigo/Estruturas/waveletTree.cpp
 */
struct wavelet_tree_updates {
    const int N, MINV, MAXV;
    vector<int> orig_arr;//TODO: let's not store this?
    vector<bit_presum> bit_presums;
    vector<bit_bit> bit_bits;//TODO: better name?
    wavelet_tree_updates(vector<int> arr, int minv, int maxv) : N(ssize(arr)), MINV(minv), MAXV(maxv), orig_arr(arr), bit_presums(MAXV - MINV, vector<bool>()), bit_bits(2 * (MAXV - MINV), 0) {
        build(arr, 0, N, MINV, MAXV, 1);
    }
    void build(vector<int>& arr, int le, int ri, int tl, int tr, int v) {
        bit_bits[v] = bit_bit(ri - le);
        if (tr - tl <= 1) return;
        int tm = split(tl, tr);
        auto low = [&](int val) -> bool {return val < tm;};
        vector<bool> bits(ri - le);
        transform(begin(arr) + le, begin(arr) + ri, begin(bits), low);
        bit_presums[v] = bit_presum(bits);
        int mi = int(stable_partition(begin(arr) + le, begin(arr) + ri, low) - begin(arr));
        build(arr, le, mi, tl, tm, 2 * v);
        build(arr, mi, ri, tm, tr, 2 * v + 1);
    }
    void set_active(int i, bool is_active) {
        //TODO: return in O(1) if active state doesn't change?
        assert(0 <= i && i < N);
        set_active_impl(i, is_active, orig_arr[i], MINV, MAXV, 1);
    }
    void set_active_impl(int i, bool is_active, int orig_value, int tl, int tr, int v) {
        bit_bits[v].set(i, is_active);
        if (tr - tl == 1) return;
        int tm = split(tl, tr), pi = bit_presums[v].popcount(i);
        //TODO: think of better condition
        if (orig_value < tm) return set_active_impl(pi, is_active, orig_value, tl, tm, 2 * v);
        set_active_impl(i - pi, is_active, orig_value, tm, tr, 2 * v + 1);
    }
    int rect_count(int le, int ri, int x, int y) const {
        assert(0 <= le && le <= ri && ri <= N && x <= y);
        return rect_count_impl(le, ri, x, y, MINV, MAXV, 1);
    }
    int rect_count_impl(int le, int ri, int x, int y, int tl, int tr, int v) const {
        if (y <= tl || tr <= x) return 0;
        if (x <= tl && tr <= y) return bit_bits[v].popcount(le, ri);
        int tm = split(tl, tr), pl = bit_presums[v].popcount(le), pr = bit_presums[v].popcount(ri);
        return rect_count_impl(pl, pr, x, y, tl, tm, 2 * v) +
               rect_count_impl(le - pl, ri - pr, x, y, tm, tr, 2 * v + 1);
    }
    int kth_smallest(int le, int ri, int k) const {
        assert(0 <= le && ri <= N);
        assert(1 <= k && k <= ri - le);//TODO: k should be <= number of active in range
        return kth_smallest_impl(le, ri, k, MINV, MAXV, 1);
    }
    int kth_smallest_impl(int le, int ri, int k, int tl, int tr, int v) const {
        if (tr - tl == 1) return tl;
        int tm = split(tl, tr), pl = bit_presums[v].popcount(le), pr = bit_presums[v].popcount(ri);
        int cnt_left = bit_bits[2 * v].popcount(pl, pr);
        if (k <= cnt_left) return kth_smallest_impl(pl, pr, k, tl, tm, 2 * v);
        return kth_smallest_impl(le - pl, ri - pr, k - cnt_left, tm, tr, 2 * v + 1);
    }
};
