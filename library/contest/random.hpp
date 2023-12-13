/** @file */
#pragma once
mt19937 rng((unsigned int)chrono::steady_clock::now().time_since_epoch().count());
/**
 * @see https://codeforces.com/blog/entry/61675
 * @code{.cpp}
 *     unsigned int x = rng();
 *
 *     // 64-bit rng
 *     mt19937_64 rng((unsigned int)chrono::steady_clock::now().time_since_epoch().count());
 *     unsigned long long x = rng();
 *
 *     // fixed seed for debugging
 *     mt19937 rng;
 *     unsigned int x = rng();
 *
 *     vector<int> a(n);
 *     shuffle(begin(a), end(a), rng);
 *
 *     vector<unsigned int> a(n);
 *     generate(begin(a), end(a), rng);
 *
 *     int x = get_rand<int>(0, 1);
 *     long long x = get_rand<long long>(1, 1e18);
 * @endcode
 * @param le,ri defines range [le, ri]
 * @returns random number in range, chosen with probability 1/(ri - le + 1)
 */
template <class T> inline T get_rand(T le, T ri) {
    assert(le <= ri);
    return uniform_int_distribution<T>(le, ri)(rng);
}
