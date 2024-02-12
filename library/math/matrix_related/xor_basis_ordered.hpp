/** @file */
#pragma once
const int lg = 60;
/**
 * @see https://codeforces.com/blog/entry/68953 https://github.com/ssk4988/Hackpack /blob/main/content/numerical/XORBasis.h
 */
struct basis {
	bitset<lg> b[lg];
	int siz = 0;
	int shrink(bitset<lg>& v) {
		for (int i = lg - 1; i >= 0; i--)
			if (v[i]) {
				if (!b[i][i]) return i;
				v ^= b[i];
			}
		return -1;
	}
	bool insert(bitset<lg>& v) {
		int i = shrink(v);
		return i >= 0 ? b[i] = v, ++siz : 0;
	}
};
