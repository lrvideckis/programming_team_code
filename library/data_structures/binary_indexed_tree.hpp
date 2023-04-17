/** @file */
#pragma once
/**
 * Binary Indexed Tree
 */
//NOLINTNEXTLINE(readability-identifier-naming)
template <typename T> struct BIT {
    vector<T> bit;
    /**
     * @param n initial size
     * @time O(n)
     */
    BIT(int n) : bit(n) {}
    /**
     * @param a initial array
     * @time O(n)
     */
    BIT(const vector<T>& a) : bit(a) {
        for (int i = 0; i < ssize(a); i++) {
            int j = i | (i + 1);
            if (j < ssize(a)) bit[j] += bit[i];
        }
    }
    /**
     * @param i index
     * @param d delta
     * @time O(log n)
     */
    void update(int i, const T& d) {
        assert(0 <= i && i < ssize(bit));
        for (; i < ssize(bit); i |= i + 1) bit[i] += d;
    }
    /**
     * @param ri defines range [0, ri)
     * @returns sum of range
     * @time O(log n)
     */
    T sum(int ri) const {
        assert(0 <= ri && ri <= ssize(bit));
        T ret = 0;
        for (; ri > 0; ri &= ri - 1) ret += bit[ri - 1];
        return ret;
    }
    /**
     * @param le,ri defines range [le, ri)
     * @returns sum of range
     * @time O(log n)
     */
    T sum(int le, int ri) const {
        assert(0 <= le && le <= ri && ri <= ssize(bit));
        return sum(ri) - sum(le);
    }
    /**
     * Requires BIT::sum(i, i + 1) >= 0
     * @param sum see return
     * @returns min pos such that sum of range [0, pos) >= sum (or n+1)
     * @time O(log n)
     */
    int lower_bound(T sum) const {
        if (sum <= 0) return 0;
        int pos = 0;
        for (int pw = 1 << __lg(ssize(bit) | 1); pw; pw >>= 1)
            if (pos + pw <= ssize(bit) && bit[pos + pw - 1] < sum)
                pos += pw, sum -= bit[pos - 1];
        return pos + 1;
    }
};
