/** @file */
#pragma once
#include "lcp_query.hpp"
/**
 * @code{.cpp}
 *     string s;
 *     lcp_query lq(s, 256);
 *     auto [le, ri] = find_substr(lq, s_le, s_ri);
 *     // or
 *     vector<int> arr;
 *     lcp_query lq(arr, 100'005);
 *     auto [le, ri] = find_substr(lq, s_le, s_ri);
 * @endcode
 *
 * @param lq lcp query
 * @param s_le,s_ri defines a substring [s_le, s_ri) of s
 * @returns a range [le, ri) such that:
 * - for all i in [le, ri): s.substr(s_le, s_ri - s_le) == s.substr(lq.sf.sa[i], s_ri - s_le)
 * - `ri - le` is the # of matches of s.substr(s_le, s_ri - s_le) in s.
 * note find_substr(i, i) returns [0, ssize(s))
 * note le < ri except when ssize(s) == 0
 * @time O(log(|s|))
 * @space O(1)
 */
template <class T> inline pair<int, int> find_substr(const lcp_query<T>& lq, int s_le, int s_ri) {
    assert(0 <= s_le && s_le <= s_ri && s_ri <= ssize(lq.sf.sa));
    if (s_le == ssize(lq.sf.sa)) return {0, ssize(lq.sf.sa)};
    auto cmp = [&](int i, bool flip) -> bool {
        return flip ^ (lq.get_lcp(i, s_le) < s_ri - s_le);
    };
    auto le = lower_bound(begin(lq.sf.sa), begin(lq.sf.sa) + lq.sf.sa_inv[s_le], 0, cmp);
    auto ri = lower_bound(begin(lq.sf.sa) + lq.sf.sa_inv[s_le] + 1, end(lq.sf.sa), 1, cmp);
    return {le - begin(lq.sf.sa), ri - begin(lq.sf.sa)};
}
