/** @file */
#pragma once
/**
 * @returns pseudo-random number
 * @code{.cpp}
 *     vector<int> a;
 *     shuffle(begin(a), end(a), rng);
 * @endcode
 */
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
/**
 * @see https://codeforces.com/blog/entry/61675
 *
 * Intended types: int, unsigned, long long
 * @param le,ri defines range [le, ri)
 * @returns random number in range
 */
template <typename T> inline T get_rand(T le, T ri) {
    assert(le < ri);
    return uniform_int_distribution<T>(le, ri - 1)(rng);
}
