#pragma once
//stress tests: tests/stress_tests/range_data_structures/seg_tree.cpp
//floor of log_2(a); index of highest 1-bit
int log_2(int a) {
	return a ? (8 * sizeof(a)) - 1 - __builtin_clz(a) : -1;
}
