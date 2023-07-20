/** @file */
#pragma once
#include "lcp_query.hpp"
/**
 * @code{.cpp}
 *     string s;
 *     lcp_query lq(s, 256);
 *     auto [le, ri] = find_substr(lq, str_le, str_ri);
 *     // or
 *     vector<int> arr;
 *     lcp_query lq(arr, 100'005);
 *     auto [le, ri] = find_substr(lq, str_le, str_ri);
 * @endcode
 *
 * @param lq lcp query
 * @param str_le,str_ri defines a substring [str_le, str_ri) of s
 * @returns a range [le, ri) such that:
 * - for all i in [le, ri): s.substr(str_le, str_ri - str_le) == s.substr(sa[i], str_ri - str_le)
 * - `ri - le` is the # of matches of s.substr(str_le, str_ri - str_le) in s.
 * note find_substr(i, i) returns [0, ssize(s))
 * note le < ri except when ssize(s) == 0
 * @time O(log(|s|))
 * @space O(1)
 */
template <typename T> inline pair<int, int> find_substr(const lcp_query<T>& lq, int str_le, int str_ri) {
    assert(0 <= str_le && str_le <= str_ri && str_ri <= ssize(lq.sf.sa));
    if (str_le == ssize(lq.sf.sa)) return {0, ssize(lq.sf.sa)};
    auto cmp = [&](int i, bool flip) -> bool {
        return flip ^ (lq.get_lcp(i, str_le) < str_ri - str_le);
    };
    auto le = lower_bound(begin(lq.sf.sa), begin(lq.sf.sa) + lq.sf.sa_inv[str_le], 0, cmp);
    auto ri = lower_bound(begin(lq.sf.sa) + lq.sf.sa_inv[str_le] + 1, end(lq.sf.sa), 1, cmp);
    return {le - begin(lq.sf.sa), ri - begin(lq.sf.sa)};
}
