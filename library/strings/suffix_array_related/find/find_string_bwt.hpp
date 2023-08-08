/** @file */
#pragma once
#include "../suffix_array.hpp"
const int K = 75, MN = '0'; // lower case letters and digits
struct find_bwt {
    int n;
    char last;
    vector<array<int, K>> occ;
    array<int, K + 1> cnt;
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
    pair<int, int> find_str(const string& t) const {
        int sa_le = 0, sa_ri = n;
        for (int i = ssize(t) - 1, x = 0; sa_le < sa_ri && i >= 0; i--) {
            char c = t[i] - MN;
            sa_le = cnt[c] + occ[sa_le][c] + (c == last && x);
            sa_ri = cnt[c] + occ[sa_ri][c] + (c == last);
            x = 1;
        }
        return {sa_le, sa_ri};
    }
};
