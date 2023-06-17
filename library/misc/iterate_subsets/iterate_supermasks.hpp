/** @file */
#pragma once
/**
 * @param mask a submask of (2^n)-1
 * @param n total number of bits
 * @param func called on all supermasks of mask
 * @time O(3^n) to iterate every supermask of every mask of size n
 * @space O(1)
 */
template <typename F> void iterate_supermasks(int mask, int n, const F& func) {
    for (int supermask = mask; supermask < (1 << n); supermask = (supermask + 1) | mask)
        func(supermask);
}
