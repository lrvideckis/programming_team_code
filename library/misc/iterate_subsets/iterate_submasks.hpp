/** @file */
#pragma once
/**
 * @author camc
 * @param mask represents a bitmask
 * @param func called on all submasks of mask
 * @time O(3^n) to iterate every submask of every mask of size n
 * @memory O(1)
 */
template <typename F> void iterate_submasks(int mask, const F& func) {
    for (int submask = mask; submask; submask = (submask - 1) & mask)
        func(submask);
}
