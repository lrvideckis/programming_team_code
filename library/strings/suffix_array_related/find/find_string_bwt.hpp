/** @file */
#pragma once
#include "../suffix_array.hpp"
const int mn = '0', len = 75; // lower case letters and digits
/**
 * Burrows Wheeler transform
 */
struct find_bwt {
    int n;
    char last;
    vector<array<int, len>> occ;
    array < int, len + 1 > cnt;
    /**
     * @code{.cpp}
     *     string s;
     *     auto [sa, sa_inv] = get_sa(s, 256);
     *     find_bwt fb(s, sa);
     * @endcode
     * @param s,sa a string and its suffix array
     * @time O(n * len)
     * @space O(n * len) for `occ` vector; it's possible to improve this
     *     to O(n * len / 64) https://codeforces.com/contest/963/submission/217802614
     */
    find_bwt(const string& s, const vector<int>& sa) : n(ssize(s)), last(s.empty() ? -1 : s.back() - mn), occ(n + 1) {
        fill(begin(cnt), end(cnt), 0);
        for (int i = 0; i < n; i++) {
            cnt[s[i] + 1 - mn]++;
            occ[i + 1] = occ[i];
            if (sa[i] == 0) continue;
            occ[i + 1][s[sa[i] - 1] - mn]++;
        }
        partial_sum(begin(cnt), end(cnt), begin(cnt));
    }
    /**
     * @param t query string
     * @returns a vector `match` where given `le` (0 <= le <= |t|) defines a suffix [le, |t|) of t:
     *     - for all i in [match[le][0], match[le][1]): t.substr(le) == s.substr(sa[i], ssize(t) - le)
     *     - `match[le][1] - match[le][0]` is the # of matches of t.substr(le) in s.
     * @time O(|t|)
     * @space an O(|t|) array is allocated and returned
     */
    vector<array<int, 2>> find_str(const string& t) const {
        vector<array<int, 2>> match(ssize(t) + 1, {0, n});
        for (int i = ssize(t) - 1; i >= 0; i--) {
            char c = t[i] - mn;
            match[i][0] = cnt[c] + occ[match[i + 1][0]][c] + (c == last && i < ssize(t) - 1);
            match[i][1] = cnt[c] + occ[match[i + 1][1]][c] + (c == last);
        }
        return match;
    }
};
