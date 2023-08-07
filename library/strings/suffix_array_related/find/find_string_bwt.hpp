/** @file */
#pragma once
#include "../suffix_array.hpp"
const int K = 75, MN = '0'; // lower case letters and digits
struct find_bwt {
    int n;
    char last;
    vector<array<int, K>> occ;
    array < int, K + 1 > cnt;
    find_bwt(const string& s, const vector<int>& sa) : n(ssize(s)), last(s.back()/*TODO empty string*/), occ(n + 1) {
        fill(begin(cnt), end(cnt), 0);
        for (char c : s) cnt[c - MN + 1]++;
        partial_sum(begin(cnt), end(cnt), begin(cnt));
        occ[0][last - MN]++;
        for (int i = 0; i < n; i++) {
            occ[i + 1] = occ[i];
            if (sa[i] == 0) continue;
            char c = s[sa[i] - 1] - MN;
            assert(c >= 0 && c < K);
            occ[i + 1][c]++;
        }
    }
    pair<int, int> find_str(const string& t) const {
        int sa_le = 0, sa_ri = n;
        for (int i = ssize(t) - 1; sa_le < sa_ri && i >= 0; i--) {
            char c = t[i] - MN;
            assert(c >= 0 && c < K);
            sa_le = cnt[c] + occ[sa_le][c] - (i == ssize(t) - 1 && t[i] == last);
            sa_ri = cnt[c] + occ[sa_ri][c];
        }
        return {sa_le, sa_ri};
    }
};
