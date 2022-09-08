#pragma once

// iterates all bitmasks of size n with k bits set
// Time Complexity: O(n choose k)
// Space Complexity: O(1)

void iterate_chooses(int n, int k, const function<void(int)>& func) {
	for (int mask = (1 << k) - 1, r, c; mask <= (1 << n) - (1 << (n - k));
	        c = mask & -mask, r = mask + c, mask = r | (((r ^ mask) >> 2) / c))
		func(mask);
}