/** @file */
#pragma once
#include "../suffix_array.hpp"
const int K = 75, MN = '0'; // lower case letters and digits
/**
 * Burrows Wheeler transform
 */
struct find_bwt {
    int n;
    char last;
    vector<array<int, K>> occ;
    array < int, K + 1 > cnt;
    /**
     * @code{.cpp}
     *     string s;
     *     auto [sa, sa_inv] = get_sa(s, 256);
     *     find_bwt fb(s, sa);
     * @endcode
     * @param s,sa a string and its suffix array
     * @time O(n * K)
     * @space O(n * K) for `occ` vector; it's possible to improve this
     *     to O(n * K / 64) https://codeforces.com/contest/963/submission/217802614
     */
    find_bwt(const string& s, const vector<int>& sa) : n(ssize(s)), last(s.empty() ? -1 : s.back() - MN), occ(n + 1) {
        fill(begin(cnt), end(cnt), 0);
        for (int i = 0; i < n; i++) {
            cnt[s[i] + 1 - MN]++;
            occ[i + 1] = occ[i];
            if (sa[i] == 0) continue;
            occ[i + 1][s[sa[i] - 1] - MN]++;
        }
        partial_sum(begin(cnt), end(cnt), begin(cnt));
    }
    /**
     * @param t query string
     * @returns range [le, ri) such that:
     *     - for all i in [le, ri): t == s.substr(sa[i], ssize(t))
     *     - `ri - le` is the # of matches of t in s.
     * @time O(|t|)
     * @space O(1)
     */
    pair<int, int> find_str(const string& t) const {
        int le = 0, ri = n;
        for (int i = ssize(t) - 1, x = 0; le < ri && i >= 0; i--) {
            char c = t[i] - MN;
            le = cnt[c] + occ[le][c] + (c == last && x);
            ri = cnt[c] + occ[ri][c] + (c == last);
            x = 1;
        }
        return {le, ri};
    }
};
