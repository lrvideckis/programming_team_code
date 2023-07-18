/** @file */
#pragma once
#include "get_lcp.hpp"
/**
 * @param str_le,str_ri defines a substring [str_le, str_ri) of s
 * @returns a range [le, ri) such that:
 * - for all i in [le, ri): s.substr(str_le, str_ri - str_le) == s.substr(sa[i], str_ri - str_le)
 * - `ri - le` is the # of matches of s.substr(str_le, str_ri - str_le) in s.
 * note find_substr(i, i) returns [0, ssize(s))
 * note le < ri except when ssize(s) == 0
 * @time O(log(|s|))
 * @space O(1)
 */
inline pair<int, int> find_substr(const sa_query& sq, int str_le, int str_ri) {
    assert(0 <= str_le && str_le <= str_ri && str_ri <= ssize(sq.s));
    if (str_le == ssize(sq.s)) return {0, ssize(sq.s)};
    auto cmp = [&](int i, bool flip) -> bool {
        return flip ^ (get_lcp(sq, i, str_le) < str_ri - str_le);
    };
    auto le = lower_bound(begin(sq.sa), begin(sq.sa) + sq.sa_inv[str_le], 0, cmp);
    auto ri = lower_bound(begin(sq.sa) + sq.sa_inv[str_le] + 1, end(sq.sa), 1, cmp);
    return {le - begin(sq.sa), ri - begin(sq.sa)};
}
