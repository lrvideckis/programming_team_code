/** @file */
#pragma once
#include "../../data_structures/sparse_table.hpp"
#include "manacher.hpp"
/**
 * @see https://codeforces.com/blog/entry/63105#comment-470339
 */
//TODO test
template <class T> struct longest_pal {
    int n;
    vector<int> man;
    RMQ<int> rmq;
    /**
     * @param s string/array
     * @time O(n log n)
     * @space O(n log n) TODO
     */
    longest_pal(const T& s) : n(ssize(s)), man(manacher(s)) {
        vector<int> idx(ssize(man));
        iota(begin(idx), end(idx), 0);
        rmq = RMQ<int>(idx, [&](int i1, int i2) -> int {return man[i1] < man[i2];});
        //rmq_ri = RMQ<int>(idx, [](int i1, int i2) -> int {return man[i1] < man[i1];});
    }
    /*
     * let 0 < i < 2*n-1
     * */
    inline int get_longest(int le, int ri) const {
        assert(0 <= le && le <= ri && ri <= n);
        int mid = (le + ri) / 2;
        int res = 0;
        {
            int idx = rmq.query(2 * le, 2 * mid);
            res = max(res, min(idx - 2 * man[idx] + 1
        }
        return min(
    }
};
