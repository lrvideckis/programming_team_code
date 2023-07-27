/** @file */
#pragma once
#include "../../data_structures/sparse_table.hpp"
#include "manacher.hpp"
template <class T> struct longest_pal_query {
    int n;
    vector<int> man, idx;
    RMQ<int> rmq;
    longest_pal_query(const T& s) : n(ssize(s)), man(manacher(s)), idx(n) {
        iota(begin(idx), end(idx), 1);
        vector<int> init(ssize(man));
        iota(begin(init), end(init), 0);
        rmq = RMQ<int>(init, [&](int i1, int i2) -> int {return len(i1) < len(i2) ? i2 : i1;});
    }
    inline int len(int i) const {return i - 2 * man[i] + 1;}
    // returns {start index, length}
    inline pair<int, int> longest_pal(int le, int ri) const {
        assert(0 <= le && le < ri && ri <= n);
        int pal_len = int(lower_bound(begin(idx), begin(idx) + (ri - le), 0, [&](int mid, int) -> bool {
            return len(rmq.query(2 * le + mid - 1, 2 * ri - mid)) >= mid;
        }) - begin(idx));
        int best_center = rmq.query(2 * le + pal_len - 1, 2 * ri - pal_len);
        return {(best_center + 1 - pal_len) / 2, pal_len};
    }
};
