/** @file */
#pragma once
random_device rd;
/**
 * @returns pseudo-random number generator
 * @code{.cpp}
 *     vector<int> a;
 *     shuffle(begin(a), end(a), rng);
 * @endcode
 *
 * use mt19937_64 rng(rd()) for 64-bit random-number generation
 */
mt19937 rng(rd());
/**
 * @see https://codeforces.com/blog/entry/61675
 *
 * Intended types: int, unsigned, long long
 * @param le,ri defines range [le, ri]
 * @returns random number in range
 */
template <class T> inline T get_rand(T le, T ri) {
    assert(le <= ri);
    return uniform_int_distribution<T>(le, ri)(rng);
}
