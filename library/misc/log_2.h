#pragma once
//floor of log_2(a); index of highest 1-bit
int log_2(int n) {
	return n > 0 ? 31 - __builtin_clz(n) : -1;
}
