/** @file */
#pragma once
#include "../suffix_array.hpp"
const int K = 75, MN = '0'; // lower case letters and digits
struct find_bwt {
    int n, idx_zero;
    char first, last;
    vector<array<int, K>> occ;
    array<int, K + 1> cnt;
    find_bwt(const string& s, const vector<int>& sa) : n(ssize(s)), first(s[0]), last(s.back()/*TODO empty string*/), occ(n + 1) {
        fill(begin(cnt), end(cnt), 0);
        for (char c : s) cnt[c - MN + 1]++;
        partial_sum(begin(cnt), end(cnt), begin(cnt));

        for (int i = 0; i <= n; i++) {
            for(int j = 0; j < K; j++) {
                assert(occ[i][j] == 0);
                //occ[i][j] = 0;
            }
        }
        occ[0][last-MN]++;
        for (int i = 0; i < n; i++) {
            occ[i + 1] = occ[i];
            if (sa[i] == 0) {
                idx_zero = i;
                continue;
            }
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
            //we have range [sa_le, sa_ri) in suffix array,
            //we want
            int nbegin = cnt[c] + occ[sa_le][c] - (i == ssize(t)-1 && t[i] == last);
            int nend = cnt[c] + occ[sa_ri][c];
            sa_le = nbegin;
            sa_ri = nend;
            assert(0 <= sa_le);
            assert(sa_le <= sa_ri);
            assert(sa_ri <= n);
        }
        return {sa_le, sa_ri};
    }
};
