/** @file */
#pragma once
#include "get_lcp.hpp"
/**
 * @code{.cpp}
 *     string s;
 *     auto [sa, sa_inv] = get_sa(s, 256);
 *     vector<int> lcp = get_lcp_array({sa, sa_inv}, s);
 *     auto [le, ri] = find_substr({sa, sa_inv}, lcp, str_le, str_ri);
 *     // or
 *     vector<int> arr;
 *     auto [sa, sa_inv] = get_sa(arr, 100'005);
 *     vector<int> lcp = get_lcp_array({sa, sa_inv}, arr);
 *     auto [le, ri] = find_substr({sa, sa_inv}, lcp, str_le, str_ri);
 * @endcode
 *
 * @param str_le,str_ri defines a substring [str_le, str_ri) of s
 * @returns a range [le, ri) such that:
 * - for all i in [le, ri): s.substr(str_le, str_ri - str_le) == s.substr(sa[i], str_ri - str_le)
 * - `ri - le` is the # of matches of s.substr(str_le, str_ri - str_le) in s.
 * note find_substr(i, i) returns [0, ssize(s))
 * note le < ri except when ssize(s) == 0
 * @time O(log(|s|))
 * @space O(1)
 */
inline pair<int, int> find_substr(const suf& sf, const vector<int>& lcp, int str_le, int str_ri) {
    assert(0 <= str_le && str_le <= str_ri && str_ri <= ssize(sf.sa));
    if (str_le == ssize(sf.sa)) return {0, ssize(sf.sa)};
    auto cmp = [&](int i, bool flip) -> bool {
        return flip ^ (get_lcp(sf.sa_inv, lcp, i, str_le) < str_ri - str_le);
    };
    auto le = lower_bound(begin(sf.sa), begin(sf.sa) + sf.sa_inv[str_le], 0, cmp);
    auto ri = lower_bound(begin(sf.sa) + sf.sa_inv[str_le] + 1, end(sf.sa), 1, cmp);
    return {le - begin(sf.sa), ri - begin(sf.sa)};
}
