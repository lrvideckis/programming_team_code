/** @file */
#pragma once
/**
 * @see https://codeforces.com/blog/entry/68953 https://codeforces.com/blog/entry/100066?#comment-887897
 * @code{.cpp}
       basis<int> b;
       basis<long long> b;
       sort(rbegin(b.b), rend(b.b)); //needed for kth smallest walk
 * @endcode
 * notes:
 *     - shrink(x) == shrink(shrink(x))
 *     - for each vector v in b: (bit_floor(v) & shrink(x)) == 0
 *     - for 0 <= i < j < ssize(b): (bit_floor(b[i]) & b[j]) == 0
 *     - for 0 <= i < j < ssize(b): bit_floor(b[i]) != bit_floor(b[j])
 */
template <class T> struct basis {
	vector<T> b;
	T shrink(T x) {
		for (T v : b) x = min(x, x ^ v);
		return x;
	}
	bool add(T x) {
		return (x = shrink(x)) ? b.push_back(x), 1 : 0;
	}
};
