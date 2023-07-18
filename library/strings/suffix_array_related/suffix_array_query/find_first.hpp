/** @file */
#pragma once
#include "constructor.hpp"
#include "find_str.hpp"
/**
 * @param t needle
 * @returns min i such that t == s.substr(i, ssize(t)) or -1. For example,
 * replace RMQ with kth-smallest PST/Wavelet to solve
 * https://open.kattis.com/problems /anothersubstringqueryproblem
 * @time O(|t| * log(|s|))
 * @space O(1)
 */
template <typename T> inline int find_first(const sa_query<T>& sq, const T& t) {
    auto [le, ri] = find_str(sq.s, sq.sa, t);
    if (le == ri) return -1;
    return sq.rmq_sa.query(le, ri);
}
