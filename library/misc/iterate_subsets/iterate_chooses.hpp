#pragma once

int next_subset(int mask) {
	int c = mask & -mask, r = mask + c;
	return r | (((r ^ mask) >> 2) / c);
}
/**
 * @brief Iterates over all bitmasks of size n with k bits set.
 * @see https://github.com/kth-competitive-programming/
 *     kactl/blob/main/content/various/chapter.tex
 * @time O(n choose k)
 * @memory O(1)
 */
void iterate_chooses(int n, int k, const function<void(int)>& func) {
	for (int mask = (1 << k) - 1; mask < (1 << n); mask = next_subset(mask))
		func(mask);
}
