#pragma once

//MUCH RANDOM!!!
seed_seq seed{
	(uint32_t)chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
	(uint32_t)random_device()(),
	(uint32_t)(uintptr_t)make_unique<char>().get(),
	(uint32_t)__builtin_ia32_rdtsc()
};
mt19937 rng(seed);

//intended types: int, unsigned
template<class T>
inline T getRand(T l, T r) {
	assert(l <= r);
	return uniform_int_distribution<T>(l, r)(rng);
}

inline double getRandReal(double l, double r) {
	assert(l < r);
	return uniform_real_distribution(l, r)(rng);
}
