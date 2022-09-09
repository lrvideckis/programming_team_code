#pragma once

//source: https://codeforces.com/blog/entry/60442

//MUCH RANDOM!!!
seed_seq seed{
	(uint32_t)chrono::duration_cast<chrono::nanoseconds>
	(chrono::high_resolution_clock::now().time_since_epoch()).count(),
	(uint32_t)random_device()(),
	(uint32_t)(uintptr_t)make_unique<char>().get(),
	(uint32_t)__builtin_ia32_rdtsc()
};
mt19937 rng(seed);

//intended types: int, unsigned, long long
//returns a random number in range [l, r)
template<class T> inline T get_rand(T l, T r) {
	assert(l < r);
	return uniform_int_distribution<T>(l, r - 1)(rng);
}
