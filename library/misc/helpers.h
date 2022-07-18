#pragma once
//floor of log_2(a); index of highest 1-bit
int log_2(int a) {
	return a ? (8 * sizeof(a)) - 1 - __builtin_clz(a) : -1;
}
