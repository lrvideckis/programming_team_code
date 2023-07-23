/** @file */
#pragma once
#include "../../data_structures/wavelet_merge/wavelet_tree.hpp"
#include "manacher.hpp"
/**
 * @see https://codeforces.com/blog/entry/63105#comment-470339
 */
//TODO test
template <class T> struct pal_count_query {
    int n;
    vector<int> man;
    wavelet_tree wt_le, wt_ri;
    pal_count_query(const T& s) : n(ssize(s)), man(manacher(s)), wt_le(man, 0, n), wt_ri(init()) {}
    wavelet_tree init() {
        //TODO: break out right into own file?
        vector<int> right(ssize(man));
        for(int i = 0; i < ssize(man); i++) {
            assert(0 <= man[i] && man[i] < n);
            right[i] = i - man[i] + 1;
            assert(1 <= right[i] && right[i] <= n);
        }
        return {right, 1, n + 1};
    }


    //number of non-empty palindromes
    inline long long count_pals(int le, int ri) const {
        assert(0 <= le && le <= ri && ri <= n);
        if(le == ri) return 0;
        int man_le = 2 * le, man_ri = 2 * ri - 1;
        assert((man_ri - man_le) % 2 == 1);
        int man_mi = (man_le + man_ri) / 2;

        //first half:
        //
        //we want sum over range [man_le, man_mi) of values:
        //    i/2 - max(man[i],le) + 1

        long long cnt = -1LL * wt_le.rect_count(man_le, man_mi, 0, le) * le;
        cnt -= wt_le.rect_sum(man_le, man_mi, le, n);

        if((man_mi-man_le)%2==1) cnt += (man_mi-1)/2 + 1LL * (man_mi-1-man_le)/2 * (man_le/2 + (man_mi-2)/2);
        else cnt += 1LL * (man_mi-man_le)/2 * (man_le/2 + (man_mi-1)/2);

        cnt += man_mi - man_le;

        //second half:
        //
        //we want sum over range [man_mi, man_ri) of values:
        //min(right[i], ri) - (i+1)/2

        cnt += 1LL * wt_ri.rect_count(man_mi, man_ri, ri, n + 1) * ri;
        cnt += wt_ri.rect_sum(man_mi, man_ri, 1, ri);

        if((man_ri-man_mi)%2==0) cnt -= 1LL * (man_ri - man_mi) / 2 * (man_ri/2 + (man_mi + 1)/2);
        else cnt -= 1LL * (man_ri - man_mi - 1) / 2 * (man_ri/2 + (man_mi + 2)/2) + (man_mi + 1) / 2;

        return cnt;
    }
};
