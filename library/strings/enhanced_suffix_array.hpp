/** @file */
#pragma once
#include "suffix_array.hpp"
#include "../data_structures/sparse_table.hpp"
#include "../monotonic_stack_related/max_rect_histogram.hpp"
/**
 * Various queries you can do based on suffix array.
 */
template <typename T> struct enhanced_sa {
    T s;
    suffix_array<T> info;
    RMQ<int> rmq_lcp, rmq_sa;
    int root_node;
    vector<int> lcp_val, le, ri;
    //vector<map<int, int>> childs;
    vector<vector<int>> childs;
    /**
     * @param a_s,max_val string/array with 0 <= a_s[i] < max_val
     * @time O((n log n) + max_val)
     * @space O(n log n) for RMQ's; O(max_val) for `freq` array used
     * temporarily in suffix_array constructor
     */
    enhanced_sa(const T& a_s, int max_val) :
        s(a_s),
        info(suffix_array(s, max_val)),
        rmq_lcp(info.lcp, [](int i, int j) -> int {return min(i, j);}),
        rmq_sa(info.sa, [](int i, int j) -> int {return min(i, j);}),
        root_node(-1) {
            auto rv = [&](int i) -> int {
                return ssize(info.lcp) - 1 - i;
            };
            vector<int> left = monotonic_stack<int>(info.lcp, less_equal());
            vector<int> right = monotonic_stack<int>(vector<int>(rbegin(info.lcp), rend(info.lcp)), less());
            for(int i = 0; i < ssize(info.lcp); i++) {
                //cout << left[i] << " " << i << " " << rv(right[rv(i)]) << endl;
                cout << left[i] + 1 << " " << rv(right[rv(i)]) << endl;
            }
        }
    /**
     * @param idx1,idx2 starting 0-based-indexes of suffixes
     * @returns max integer k such that s.substr(idx1, k) == s.substr(idx2, k)
     * @time O(1)
     * @space O(1)
     */
    inline int get_lcp(int idx1, int idx2) const {
        if (idx1 == idx2) return ssize(s) - idx1;
        auto [le, ri] = minmax(info.rank[idx1], info.rank[idx2]);
        return rmq_lcp.query(le, ri);
    }
    /**
     * @param idx1,idx2 starting 0-based-indexes of suffixes
     * @returns 1 iff suffix s.substr(idx1) < s.substr(idx2)
     * @time O(1)
     * @space O(1)
     */
    inline bool less(int idx1, int idx2) const {
        return info.rank[idx1] < info.rank[idx2];
    }
    /**
     * @see https://github.com/yosupo06/Algorithm/blob /master/src/string/suffixarray.hpp
     * @param t needle
     * @returns range [le, ri) such that:
     * - for all i in [le, ri): t == s.substr(info.sa[i], ssize(t))
     * - `ri - le` is the # of matches of t in s.
     * @time O(|t| * log(|s|))
     * @space O(1)
     */
    pair<int, int> find(const T& t) const {
        if(root_node == -1) {//TODO: find a way to not have to special case this
            assert(ssize(info.sa) <= 1);
            return (ssize(t) == 1 && s == t) ? pair(0, 1) : pair(0, 0);
        }
        assert(ssize(info.sa) >= 2);
        //subarray [le[v], ri[v]] in info.sa
        //lcp_val[v] = min of [le[v], ri[v]) in info.lcp
        //cout << "query t: " << t << endl;
        int v = root_node;
        int matched_so_far = 0;
        while(1) {
            //cout << "here, interval: " << lcp_val[v] << "    " << le[v] << " " << ri[v] << endl;
            assert(matched_so_far <= lcp_val[v]);
            {
                int cnt_to_match = min(lcp_val[v], ssize(t)) - matched_so_far;
                assert(cnt_to_match <= ssize(t));
                if(s.compare(info.sa[le[v]] + matched_so_far, cnt_to_match, t, matched_so_far, cnt_to_match) != 0) {
                    return {0,0};
                }
            }
            if(lcp_val[v] >= ssize(t)) {
                //cout << "return case 2" << endl;
                return {le[v], ri[v] + 1};
            }
            matched_so_far = lcp_val[v];
            bool found = 0;
            for(int child : childs[v]) {
                if(t[matched_so_far] == s[info.sa[le[child]] + matched_so_far]) {
                    //cout << "found child" << endl;
                    found = 1;
                    v = child;
                }
            }
            if(found) continue;
            for(int i = le[v]; i <= ri[v]; i++) {
                if(s.compare(info.sa[i] + matched_so_far, ssize(t) - matched_so_far, t, matched_so_far, ssize(t) - matched_so_far) == 0) {
                    //cout << "return case 3" << endl;
                    return {i, i + 1};
                }
            }
            if(!found) {
                //cout << "return case 4" << endl;
                return {0,0};
            }
        }
        assert(0);
    }
    /**
     * @param t needle
     * @returns min i such that t == s.substr(i, ssize(t)) or -1. For example,
     * replace RMQ with kth-smallest PST/Wavelet to solve
     * https://open.kattis.com/problems /anothersubstringqueryproblem
     * @time O(|t| * log(|s|))
     * @space O(1)
     */
    int find_first(const T& t) const {
        auto [le, ri] = find(t);
        if (le == ri) return -1;
        return rmq_sa.query(le, ri);
    }
};
