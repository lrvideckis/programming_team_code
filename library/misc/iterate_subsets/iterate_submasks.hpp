#pragma once
/**
 * @brief Iterates over all submasks of mask.
 * @time O(3^n) to iterate every submask of every mask of size n
 * @memory O(1)
 */
void iterate_submasks(int mask, const function<void(int)>& func) {
	for (int submask = mask; submask; submask = (submask - 1) & mask)
		func(submask);
}
