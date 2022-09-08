#pragma once

// iterates all bitmasks of size n with k bits set
// Time Complexity: O(n choose k)
// Space Complexity: O(1)

int next_subset(int mask) {
	int c = mask & -mask, r = mask + c;
	return r | (((r ^ mask) >> 2) / c);
}

void iterate_chooses(int n, int k, const function<void(int)>& func) {
	for (int mask = (1 << k) - 1; mask <= (1 << n) - (1 << (n - k)); mask = next_subset(mask))
		func(mask);
}
