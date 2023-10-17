/** @file */
#pragma once
/**
 * Binary Indexed Tree
 */
//NOLINTNEXTLINE(readability-identifier-naming)
template <class T> struct BIT {
    vector<T> s;
    BIT() {}
    /**
     * @param n initial size
     * @time O(n)
     * @space O(n) for `s` vector
     */
    BIT(int n) : s(n) {}
    /**
     * @param a initial array
     * @time O(n)
     * @space O(n) for `s` vector
     */
    BIT(const vector<T>& a) : s(a) {
        for (int i = 0; i < ssize(a); i++) {
            int j = i | (i + 1);
            if (j < ssize(a)) s[j] += s[i];
        }
    }
    /**
     * @param i index
     * @param d delta
     * @time O(log n)
     * @space O(1)
     */
    inline void update(int i, T d) {
        assert(0 <= i && i < ssize(s));
        for (; i < ssize(s); i |= i + 1) s[i] += d;
    }
    /**
     * @param ri defines range [0, ri)
     * @returns arr[0] + arr[1] + ... + arr[ri - 1]
     * @time O(log n)
     * @space O(1)
     */
    inline T sum(int ri) const {
        assert(0 <= ri && ri <= ssize(s));
        T ret = 0;
        for (; ri > 0; ri &= ri - 1) ret += s[ri - 1];
        return ret;
    }
    /**
     * @param le,ri defines range [le, ri)
     * @returns arr[le] + arr[le + 1] + ... + arr[ri - 1]
     * @time O(log n)
     * @space O(1)
     */
    inline T sum(int le, int ri) const {
        assert(le <= ri);
        return sum(ri) - sum(le);
    }
};
