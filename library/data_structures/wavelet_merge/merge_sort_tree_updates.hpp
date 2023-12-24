/** @file */
#pragma once
#include "bool_presum.hpp"
#include "bool_bit.hpp"
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
    int n;
    vector<int> sorted, perm;
    vector<bool_presum> bool_presums;
    vector<bool_bit> bool_bits;
    /**
     * @param a array
     * @param active active[i] == 1 iff index i is initially active
     * @time O(n log n)
     * @space O(n + (n log n) / 64) for `bool_presums` vector
     *        O(n + (n log n) / 64) for `bool_bits` vector
     */
    merge_sort_tree_updates(const vector<int>& a, const vector<bool>& active) : n(ssize(a)), sorted(n), perm(n), bool_presums(n, vector<bool>()), bool_bits(2 * n, vector<bool>()) {
        assert(ssize(active) == n);
        if (!n) return;
        vector<pair<int, bool>> cpy(n);
        for (int i = 0; i < n; i++) cpy[i].first = i;
        build(a, active, cpy, 0, n, 1);
        for (int i = 0; i < n; i++) {
            perm[cpy[i].first] = i;
            sorted[i] = a[cpy[i].first];
        }
    }
    void build(const vector<int>& a, const vector<bool>& active, vector<pair<int, bool>>& cpy, int tl, int tr, int u) {
        if (tr - tl == 1) {
            bool_bits[u] = bool_bit(vector<bool>(1, active[tl]));
            return;
        }
        int tm = split(tl, tr);
        build(a, active, cpy, tl, tm, 2 * u);
        build(a, active, cpy, tm, tr, 2 * u + 1);
        for (int i = tl; i < tr; i++) cpy[i].second = i < tm;
        inplace_merge(begin(cpy) + tl, begin(cpy) + tm, begin(cpy) + tr, [&](auto i, auto j) {return a[i.first] < a[j.first];});
        vector<bool> bools(tr - tl);
        transform(begin(cpy) + tl, begin(cpy) + tr, begin(bools), [](auto val) {return val.second;});
        bool_presums[u] = bool_presum(bools);
        transform(begin(cpy) + tl, begin(cpy) + tr, begin(bools), [&](auto val) {return active[val.first];});
        bool_bits[u] = bool_bit(bools);
    }
    /**
     * @param i index
     * @param is_active we want to set active[i] = is_active
     * @time O(log(n) * log(n / 64))
     * @space O(log(n)) for recursive stack
     */
    void set_active(int i, bool is_active) {
        assert(0 <= i && i < n);
        if (bool_bits[1].on(perm[i]) == is_active) return;
        set_active_impl(perm[i], is_active, 0, n, 1);
    }
    void set_active_impl(int i, bool is_active, int tl, int tr, int u) {
        bool_bits[u].set(i, is_active);
        if (tr - tl == 1) return;
        int tm = split(tl, tr), pi = bool_presums[u].popcount(i);
        if (bool_presums[u].on(i)) return set_active_impl(pi, is_active, tl, tm, 2 * u);
        set_active_impl(i - pi, is_active, tm, tr, 2 * u + 1);
    }
    /**
     * @param le,ri,x,y defines rectangle: indexes in [le, ri), values in [x, y)
     * @returns number of active indexes i such that le <= i < ri and x <= a[i] < y
     * @time O(log(n))
     * @space O(log(n)) for recursive stack
     */
    int rect_count(int le, int ri, int x, int y) {
        assert(0 <= le && le <= ri && ri <= n && x <= y);
        int xi = int(lower_bound(begin(sorted), end(sorted), x) - begin(sorted));
        int yi = int(lower_bound(begin(sorted), end(sorted), y) - begin(sorted));
        return rect_count_impl(le, ri, xi, yi, 0, n, 1);
    }
    int rect_count_impl(int le, int ri, int xi, int yi, int tl, int tr, int u) {
        if (ri <= tl || tr <= le) return 0;
        if (le <= tl && tr <= ri) return bool_bits[u].popcount(xi, yi);
        int tm = split(tl, tr), pl = bool_presums[u].popcount(xi), pr = bool_presums[u].popcount(yi);
        return rect_count_impl(le, ri, pl, pr, tl, tm, 2 * u) +
               rect_count_impl(le, ri, xi - pl, yi - pr, tm, tr, 2 * u + 1);
    }
    /**
     * @param x,y defines range of values [x, y)
     * @param k must satisfy 1 <= k <= number of active indexes i such that x <= a[i] < y
     * @returns the kth smallest active index i such that x <= a[i] < y
     *     - kth_smallest(x,y,1) returns the smallest active index i such that x <= a[i] < y
     *     - kth_smallest(x,y,rect_count(0,n,x,y)) returns the largest active index i such that x <= a[i] < y
     * @time O(log(n))
     * @space O(log(n)) for recursive stack
     */
    int kth_smallest(int x, int y, int k) {
        int xi = int(lower_bound(begin(sorted), end(sorted), x) - begin(sorted));
        int yi = int(lower_bound(begin(sorted), end(sorted), y) - begin(sorted));
        assert(1 <= k && k <= bool_bits[1].popcount(xi, yi));
        return kth_smallest_impl(xi, yi, k, 0, n, 1);
    }
    int kth_smallest_impl(int xi, int yi, int k, int tl, int tr, int u) {
        if (tr - tl == 1) return tl;
        int tm = split(tl, tr), pl = bool_presums[u].popcount(xi), pr = bool_presums[u].popcount(yi);
        int cnt_left = bool_bits[2 * u].popcount(pl, pr);
        if (k <= cnt_left) return kth_smallest_impl(pl, pr, k, tl, tm, 2 * u);
        return kth_smallest_impl(xi - pl, yi - pr, k - cnt_left, tm, tr, 2 * u + 1);
    }
};
