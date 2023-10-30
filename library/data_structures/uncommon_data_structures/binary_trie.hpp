/** @file */
#pragma once
/**
 * Trie on bits. Can be thought of as a multiset of integers.
 */
template <class T> struct binary_trie {
    int mx_bit;
    struct node {
        T val = -1;
        int sub_sz = 0;
        array<int, 2> next = {-1, -1};
    };
    vector<node> t;
    /**
     * @code{.cpp}
     *     binary_trie<int> bt; //mx_bit = 30
     *     // or
     *     binary_trie<long long> bt; //mx_bit = 62
     * @endcode
     */
    binary_trie() : mx_bit(8 * sizeof(T) - 2), t(1) {}
    /**
     * @param val integer
     * @param delta 1 to insert val, -1 to remove val
     * @returns number of occurances of val in multiset
     * @time O(mx_bit)
     * @space O(mx_bit) new nodes are pushed back onto `t`
     */
    int update(T val, int delta) {
        int u = 0;
        t[0].sub_sz += delta;
        for (int bit = mx_bit; bit >= 0; bit--) {
            bool v = (val >> bit) & 1;
            if (t[u].next[v] == -1) {
                t[u].next[v] = int(ssize(t));
                t.emplace_back();
            }
            u = t[u].next[v];
            t[u].sub_sz += delta;
        }
        t[u].val = val;
        return t[u].sub_sz;
    }
    /**
     * @returns number of integers in this multiset.
     */
    inline int size() {
        return t[0].sub_sz;
    }
    /**
     * @param val query parameter
     * @returns integer x such that x is in this multiset, and the value of
     * (x^val) is minimum.
     * @time O(mx_bit)
     * @space O(1)
     */
    T min_xor(T val) {
        assert(size() > 0);
        int u = 0;
        for (int bit = mx_bit; bit >= 0; bit--) {
            bool v = (val >> bit) & 1;
            int ch = t[u].next[v];
            if (ch != -1 && t[ch].sub_sz > 0)
                u = ch;
            else
                u = t[u].next[!v];
        }
        return t[u].val;
    }
};
