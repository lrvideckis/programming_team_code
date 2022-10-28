#pragma once

//source: https://codeforces.com/blog/entry/61675

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//intended types: int, unsigned, long long
//returns a random number in range [le, ri)
template <typename T> inline T get_rand(T le, T ri) {
	assert(le < ri);
	return uniform_int_distribution<T>(le, ri - 1)(rng);
}

//vector<int> a;
//shuffle(a.begin(), a.end(), rng);
