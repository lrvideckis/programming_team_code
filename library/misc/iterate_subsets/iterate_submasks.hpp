#pragma once

// iterates all submasks of mask
// Time Complexity: O(3^n) to iterate every submask of every mask of size n
// Space Complexity: O(1)

void iterate_submasks(int mask, const function<void(int)>& func) {
	for (int submask = mask; submask; submask = (submask - 1) & mask)
		func(submask);
}