/** @file */
#pragma once
#include "../../data_structures/sparse_table.hpp"
#include "manacher.hpp"
/**
 * @see https://codeforces.com/blog/entry/63105#comment-470339
 */
//TODO test
template <class T> struct longest_pal_query {
    int n;
    vector<int> man, idx;
    RMQ<int> rmq;
    /**
     * @param s string/array
     * @time O(n log n)
     * @space O(n log n) TODO
     */
    longest_pal_query(const T& s) : n(ssize(s)), man(manacher(s)), idx(ssize(man)) {
        iota(begin(idx), end(idx), 0);
        rmq = RMQ<int>(idx, [&](int i1, int i2) -> int {return i1-2*man[i1]+1 < i2-2*man[i2]+1 ? i2 : i1;});
    }
    inline int get_longest(int le, int ri) const {
        assert(0 <= le && le <= ri && ri <= n);
        if(le == ri) return 0;//TODO remove special case
        int man_le = 2 * le, man_ri = 2 * ri - 1;
        assert(2 * (ri-le) - 1 == man_ri - man_le);
        assert((man_ri - man_le) % 2 == 1);
        int start = 0, end = ri - le + 1;
        while(start + 1 < end) {
            int mid = (start + end) / 2;
            //is there some palindromic substring with length >= mid ?
            //
            //odd length palindrome; left half:
            //only consider c such that 2*(c/2 - le)+1 >= mid
            //c-2*le+1 >= mid
            //c >= mid+2*le-1 = man_le+mid-1
            //
            //2*(c/2 - man[c])+1 >= mid
            //
            //-------
            //
            //even length palindrome; left half:
            //only consider c such that 2*((c+1)/2 - le) >= mid
            //(c+1) - 2*le >= mid
            //
            //
            //
            //
            //-----------------------------------------------------------
            //
            //odd length palindrome; right half:
            //only consider c such that: 2 * (ri-1 - c/2) + 1 >= mid
            //2*ri - 1 - c >= mid
            //2*ri - 1 - mid >= c
            //c <= 2*ri - 1 - mid
            //c < 2*ri - mid
            //
            //
            //even length palindrome; right half:
            //only consider c such that: 2*(ri - (c+1)/2) >= mid
            //2*ri - c-1 >= mid
            //-2*ri + c + 1 <= -mid
            //c <= 2*ri - 1 - mid
            //c < 2*ri-mid
            //
            //


            if(man_le + mid-1 >= 2*ri - mid) {
                end = mid;
                continue;
            }
            int i = rmq.query(man_le + mid-1, 2*ri - mid);
            if(i-2*man[i]+1 >= mid) start = mid;
            else end = mid;
        }
        return start;
    }
};

    /*
inline pair<int, int> get_range(int str_le, int str_ri) const {
		assert(str_le <= str_ri);
		int i = sa_inv[str_le];
		int le = i;
		// replace with some lower_bound
		for (int p = __lg(ssize(sa)); p >= 0; p--) {
			int mi = le - (1 << p);
			if (mi < 0)
				continue;
			if (get_lcp(sa[mi], str_le) >= str_ri - str_le)
				le = mi;
		}
		int ri = i;
		// replace with some lower_bound
		for (int p = __lg(ssize(sa)); p >= 0; p--) {
			int mi = ri + (1 << p);
			if (mi >= ssize(sa))
				continue;
			if (get_lcp(sa[mi], str_le) >= str_ri - str_le)
				ri = mi;
		}
		return {le, ri + 1};
	}
    */
