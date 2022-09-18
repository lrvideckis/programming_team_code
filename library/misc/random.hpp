#pragma once

//source: https://codeforces.com/blog/entry/61675

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//intended types: int, unsigned, long long
//returns a random number in range [l, r)
template<class T> inline T get_rand(T l, T r) {
	assert(l < r);
	return uniform_int_distribution<T>(l, r - 1)(rng);
}

//vector<int> a;
//shuffle(a.begin(), a.end(), rng);
