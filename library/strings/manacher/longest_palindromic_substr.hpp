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
    vector<int> man;
    RMQ<int> rmq;
    /**
     * @param s string/array
     * @time O(n log n)
     * @space O(n log n) TODO
     */
    longest_pal_query(const T& s) : n(ssize(s)), man(manacher(s)),
        rmq(man, [&](int x, int y) -> int {return min(x, y);}) {
        //vector<int> idx(ssize(man));
        //iota(begin(idx), end(idx), 0);
        //rmq = RMQ<int>(idx, [&](int i1, int i2) -> int {return man[i1] < man[i2];});
        //rmq_ri = RMQ<int>(idx, [](int i1, int i2) -> int {return man[i1] < man[i1];});
    }
    /**
     * let mid be given from binary search
     * [le, ri)
     * [le, mi); [mi, ri)
     *
     * let 0 < i < 2*n-1
     * for odd len. palindromes (so i is even)
     * mid[i]
     *
     */
    inline int get_longest(int le, int ri) const {
        assert(0 <= le && le <= ri && ri <= n);
        if(le == ri) return 0;//TODO remove special case
        int man_le = 2 * le, man_ri = 2 * ri - 1;
        assert((man_ri - man_le) % 2 == 1);

        int man_mi = (man_ri + man_le) / 2;

        {
            //range [le, mi)
            int start = 0, end = man_mi - man_le;
            while(start + 1 < end) {
                int mid = (start + end) / 2;
                //is there some palindromic substring with radius >= mid ?
                //
                //for odd length palindromes, 2 * radius + 1 == len (so radius doesn't include middle)
                //
                //so it must have middle index i >= le + mid
                //
                //for odd length palindromes, man[2*x] is min start index of palindrome for middle at index x
                //
                // -------
                //
                //for even len palindromes, if middle is at indexes [x, x+2)
                //
                //2 * radius == len
                //
                //must have x >= le + mid
                //
                //
                if(rmq.query(2 * (le + mid), 2 * mi) <= le) start = mid;
                else end = mid;
            }
        }
        {
            //range [mi, ri)
        }
        return min(
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
