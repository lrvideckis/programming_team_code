#pragma once
/**
 * Iterates over all supermasks of mask.
 * @time O(3^n) to iterate every supermask of every mask of size n
 * @memory O(1)
 */
void iterate_supermasks(int mask, int n, const function<void(int)>& func) {
	for (int supermask = mask; supermask < (1 << n); supermask = (supermask + 1) | mask)
		func(supermask);
}
