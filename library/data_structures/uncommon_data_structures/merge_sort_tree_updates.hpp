/** @file */
#pragma once
#include "bit_presum.hpp"
#include "bit_bit.hpp"
/**
 * @see https://codeforces.com/blog/entry/112755
 * @param tl,tr defines range [tl, tr)
 * @returns split point of range which makes the merge sort tree a complete
 * binary tree
 */
inline int split(int tl, int tr) {
    int pw2 = 1 << __lg(tr - tl);
    return min(tl + pw2, tr - pw2 / 2);
}
/**
 * merge sort tree with toggle element active point update
 */
struct merge_sort_tree_updates {
    const int N;
    vector<int> sorted, perm;
    vector<bit_presum> bit_presums;
    vector<bit_bit> bit_bits;
    /**
     * @param a_arr array
     * @time O(n log n)
     * @space O(n + (n log n) / 64) for `bit_presums` vector
     *        O(n + (n log n) / 64) for `bit_bits` vector
     */
    merge_sort_tree_updates(const vector<int>& arr) : N(ssize(arr)), sorted(N), perm(N), bit_presums(N, vector<bool>()), bit_bits(max(2, 2 * N), 0) {
        vector<pair<int, bool>> cpy(N);
        for (int i = 0; i < N; i++) cpy[i].first = i;
        build(arr, cpy, 0, N, 1);
        for (int i = 0; i < N; i++) {
            perm[cpy[i].first] = i;
            sorted[i] = arr[cpy[i].first];
        }
    }
    void build(const vector<int>& arr, vector<pair<int, bool>>& cpy, int tl, int tr, int v) {
        bit_bits[v] = bit_bit(tr - tl);
        if (tr - tl <= 1) return;
        int tm = split(tl, tr);
        build(arr, cpy, tl, tm, 2 * v);
        build(arr, cpy, tm, tr, 2 * v + 1);
        for (int i = tl; i < tr; i++) cpy[i].second = i < tm;
        inplace_merge(begin(cpy) + tl, begin(cpy) + tm, begin(cpy) + tr, [&](auto i, auto j) {return arr[i.first] < arr[j.first];});
        vector<bool> bits(tr - tl);
        transform(begin(cpy) + tl, begin(cpy) + tr, begin(bits), [](auto val) {return val.second;});
        bit_presums[v] = bit_presum(bits);
    }
    /**
     * @param le,ri,x,y defines rectangle: indexes in [le, ri), values in [x, y)
     * @returns sum of values arr[i] such that le <= i < ri and x <= arr[i] < y
     * @time O(log(n))
     * @space O(log(n)) for recursive stack
     */
    int query(int le, int ri, int x, int y) const {
        assert(0 <= le && le <= ri && ri <= N && x <= y);
        int xi = int(lower_bound(begin(sorted), end(sorted), x) - begin(sorted));
        int yi = int(lower_bound(begin(sorted), end(sorted), y) - begin(sorted));
        return query_impl(le, ri, xi, yi, 0, N, 1);
    }
    int query_impl(int le, int ri, int xi, int yi, int tl, int tr, int v) const {
        if (ri <= tl || tr <= le) return 0;
        if (le <= tl && tr <= ri) return bit_bits[v].popcount(xi, yi);
        int tm = split(tl, tr), pl = bit_presums[v].popcount(xi), pr = bit_presums[v].popcount(yi);
        return query_impl(le, ri, pl, pr, tl, tm, 2 * v) +
               query_impl(le, ri, xi - pl, yi - pr, tm, tr, 2 * v + 1);
    }
    /**
     * @param i index
     * @param is_active we want to set active_state[i] = is_active
     * @time O(log(n) * log(n / 64))
     * @space O(log(n)) for recursive stack
     */
    void set_active(int i, bool is_active) {
        assert(0 <= i && i < N);
        if (bit_bits[1].on(perm[i]) == is_active) return;
        set_active_impl(perm[i], is_active, 0, N, 1);
    }
    void set_active_impl(int i, bool is_active, int tl, int tr, int v) {
        bit_bits[v].set(i, is_active);
        if (tr - tl == 1) return;
        int tm = split(tl, tr), pi = bit_presums[v].popcount(i);
        if (bit_presums[v].on(i)) return set_active_impl(pi, is_active, tl, tm, 2 * v);
        set_active_impl(i - pi, is_active, tm, tr, 2 * v + 1);
    }
};
