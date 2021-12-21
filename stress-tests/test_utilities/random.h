#pragma once

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int l, int r) {
	assert(l <= r);
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

inline double getRandReal(double l, double r) {
	assert(l < r);
	uniform_real_distribution<double> uid(l, r);
	return uid(rng);
}
