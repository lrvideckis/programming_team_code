#pragma once
//floor of log_2(a); index of highest 1-bit
//returns lg, the smallest int such that 2^lg >= n
int log_2(int n) {
	return n > 0 ? 31 - __builtin_clz(n) : -1;
}
