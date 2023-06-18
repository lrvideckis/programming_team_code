/** @file */
#pragma once
#include "../../kactl/content/strings/Manacher.h"
/**
 * Interface on top of manacher array
 */
struct pal_query {
    const int N;
    array<vi, 2> pal_len; /**< half the length of palindrome for each center */
    /**
     * @param s string
     * @time O(n)
     * @space O(n) for `pal_len` array
     */
    pal_query(const string& s) : N(ssize(s)), pal_len(manacher(s)) {}
    /**
     * @param le,ri defines substring [le,ri)
     * @returns 1 iff s.substr(le, ri - le) is a palindrome (so 1 when le == ri)
     * @time O(1)
     */
    inline bool is_pal(int le, int ri) const {
        assert(0 <= le && le <= ri && ri <= N);
        auto [quot, rem] = div(ri - le, 2);
        return pal_len[rem][le + quot] >= quot;
    }
};
