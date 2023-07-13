/** @file */
#pragma once
#include "suffix_array.hpp"
#include "../data_structures/sparse_table.hpp"
#include <stack>
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
        rmq_sa(info.sa, [](int i, int j) -> int {return min(i, j);}) {

            int last_interval = -1;
            stack<int> st;

            for(int i = 0; i < ssize(info.lcp); i++) {
                int farthest_left = i;
                while(!st.empty() && lcp_val[st.top()] > info.lcp[i]) {
                    //here, interval [st.top().second, i]
                    last_interval = st.top();
                    st.pop();
                    ri[last_interval] = i;
                    assert(le[last_interval] < farthest_left);
                    farthest_left = le[last_interval];
                    if(!st.empty() && lcp_val[st.top()] >= info.lcp[i]) {
                        childs[st.top()].push_back(last_interval);
                        last_interval = -1;
                    }
                }
                if(st.empty() || lcp_val[st.top()] < info.lcp[i]) {
                    st.push(ssize(le));
                    childs.emplace_back();
                    if(last_interval != -1) childs.back().push_back(last_interval);
                    last_interval = -1;
                    lcp_val.push_back(info.lcp[i]);
                    le.push_back(farthest_left);
                    ri.push_back(ssize(info.lcp));
                }
            }
            while(!st.empty()) {
                root_node = last_interval = st.top();
                st.pop();
                if(!st.empty()) {
                    childs[st.top()].push_back(last_interval);
                }
            }
            assert(le[root_node] == 0 && ri[root_node] == ssize(info.lcp));
            for(int i = 0; i < ssize(childs); i++) {
                for(int j : childs[i]) {
                    assert(le[i] <= le[j] && le[j] < ri[j] && ri[j] <= ri[i]);
                }
                for(int j = 1; j < ssize(childs[i]); j++) {
                    assert(ri[childs[i][j-1]] < le[childs[i][j]]);
                }
            }
            /*
            for(int i = 0; i < ssize(childs); i++) {
                cout << lcp_val[i] << "    " << le[i] << " " << ri[i] << endl;
            }
            for(int i = 0; i < ssize(childs); i++) {
                for(int j : childs[i]) {
                    cout << "edge: " << lcp_val[i] << "   " << le[i] << " " << ri[i] << " -> " << lcp_val[j] << "    " << le[j] << " " << ri[j] << endl;
                }
            }
            */
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
