/** @file */
#pragma once
/**
 * Trie on bits. Can be thought of as a multiset of integers.
 */
struct binary_trie {
    const int MX_BIT = 62; /**< or 30 for ints */
    struct node {
        long long val = -1;
        int sub_sz = 0;
        array<int, 2> next = {-1, -1};
    };
    vector<node> t; /**< stores trie */
    binary_trie() : t(1) {}
    /**
     * @param val integer
     * @param delta 1 to insert val, -1 to remove val
     * @returns number of occurances of val in multiset
     * @time O(MX_BIT)
     */
    int update(long long val, int delta) {
        int c = 0;
        t[0].sub_sz += delta;
        for (int bit = MX_BIT; bit >= 0; bit--) {
            bool v = (val >> bit) & 1;
            if (t[c].next[v] == -1) {
                t[c].next[v] = ssize(t);
                t.emplace_back();
            }
            c = t[c].next[v];
            t[c].sub_sz += delta;
        }
        t[c].val = val;
        return t[c].sub_sz;
    }
    /**
     * @returns number of integers in this multiset.
     */
    int size() const {
        return t[0].sub_sz;
    }
    /**
     * @param val query parameter
     * @returns integer x such that x is in this multiset, and the value of
     * (x^val) is minimum.
     * @time O(MX_BIT)
     */
    long long min_xor(long long val) const {
        assert(size() > 0);
        int c = 0;
        for (int bit = MX_BIT; bit >= 0; bit--) {
            bool v = (val >> bit) & 1;
            int ch = t[c].next[v];
            if (ch != -1 && t[ch].sub_sz > 0)
                c = ch;
            else
                c = t[c].next[!v];
        }
        return t[c].val;
    }
};
