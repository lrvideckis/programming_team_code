/** @file */
#pragma once
#include "find_str.hpp"
/**
 * @param t needle
 * @returns min i such that t == s.substr(i, ssize(t)) or -1. For example,
 * replace RMQ with kth-smallest PST/Wavelet to solve
 * https://open.kattis.com/problems /anothersubstringqueryproblem
 * @time O(|t| * log(|s|))
 * @space O(1)
 */
template <typename T> inline int find_first(const T& s, const vector<int>& sa, const T& t) {
    static RMQ<int> rmq_sa(sa, [](int x, int y) -> int {return min(x, y);});
    auto [le, ri] = find_str(s, sa, t);
    if (le == ri) return -1;
    return rmq_sa.query(le, ri);
}
