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
    vector<map<int, int>> lcp_tree;
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
        root_node(-1),
        lcp_tree(ssize(info.lcp)) {

            //for(int val : info.lcp) cout << val << " ";
            //cout << endl;

            tie(le, ri) = get_range(info.lcp);

            auto is_node = [&](int i) -> bool {
                assert(0 <= i && i < ssize(info.lcp));
                return le[i] == -1 || info.lcp[le[i]] < info.lcp[i];
            };

            vector<int> leftmost_min(ssize(info.lcp));
            iota(begin(leftmost_min), end(leftmost_min), 0);
            for(int i = 0; i < ssize(info.lcp); i++) {
                if(!is_node(i)) {
                    leftmost_min[i] = leftmost_min[le[i]];
                }
            }
            //min cartesian tree: move to cartesian tree file

            vector<vector<int>> adj(ssize(info.lcp));

            for(int i = 0; i < ssize(info.lcp); i++) {
                if(le[i] == -1 && ri[i] == ssize(info.lcp)) {
                    assert(root_node == -1);
                    root_node = i;
                } else if(is_node(i)) {
                    bool le_par = (le[i] >= 0 && (ri[i] == ssize(info.lcp) || info.lcp[le[i]] > info.lcp[ri[i]]));
                    int par = leftmost_min[le_par ? le[i] : ri[i]];
                    assert(info.lcp[par] < info.lcp[i]);
                    assert(le[par] <= le[i] && ri[i] <= ri[par]);
                    //cout << "edge: " << le[par]+1 << " " << ri[par] << " -> " << le[i]+1 << " " << ri[i] << "    ";
                    assert(info.sa[i] + info.lcp[par] < ssize(s));
                    //cout << "letter: " << s[info.sa[i] + info.lcp[par]] << endl;//correct
                    adj[par].push_back(i);
                }
            }
            if(root_node == -1) return;

            assert(ssize(adj) == ssize(info.lcp));
            //convert and add childs
            queue<int> q({root_node});
            while(!q.empty()) {
                int u = q.front();
                //node u's inclusive-exclusive range: [ le[u]+1, ri[u] )
                q.pop();
                int prev = le[u] + 1;
                for(int v : adj[u]) {
                    //add leaves between last child interval and this interval
                    for(int i = prev; i <= le[v]; i++) {
                        assert(lcp_tree[u].emplace(s[info.sa[i] + info.lcp[u]], ssize(info.lcp) + i).second);
                    }
                    assert(lcp_tree[u].emplace(s[info.sa[v] + info.lcp[u]], v).second);
                    prev = ri[v] + 1;
                    q.push(v);
                }
                //add leaves after last child interval
                for(int i = prev; i <= ri[u]; i++) {
                    assert(lcp_tree[u].emplace(s[info.sa[i] + info.lcp[u]], ssize(info.lcp) + i).second);
                }
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
        int u = root_node;
        int cnt_matched = 0;
        while(u < ssize(info.lcp)) {
            {
                int cnt_to_match = min(info.lcp[u], ssize(t)) - cnt_matched;
                assert(0 <= cnt_to_match && cnt_to_match <= ssize(t));
                if(s.compare(info.sa[le[u] + 1] + cnt_matched, cnt_to_match, t, cnt_matched, cnt_to_match) != 0) {
                    return {0,0};//TODO: return {le[u]+1, le[u]+1} ?
                }
            }
            if(info.lcp[u] >= ssize(t)) {
                //cout << "return case 2" << endl;
                return {le[u] + 1, ri[u] + 1};
            }
            cnt_matched = info.lcp[u];
            auto it = lcp_tree[u].find(t[cnt_matched]);
            if(it == lcp_tree[u].end()) {
                return {0,0};//TODO: see above todo
            }
            u = it->second;
        }
        //reached leaf node
        u -= ssize(info.lcp);
        assert(0 <= u && u < ssize(info.sa));
        int cnt_to_match = ssize(t) - cnt_matched;
        if(ssize(s) - info.sa[u] < cnt_to_match) return {0,0};
        assert(0 <= cnt_to_match && cnt_to_match <= ssize(t));
        if(s.compare(info.sa[u] + cnt_matched, cnt_to_match, t, cnt_matched, cnt_to_match) != 0) {
            return {0,0};//TODO: return {le[u]+1, le[u]+1} ?
        }
        return {u, u + 1};
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
