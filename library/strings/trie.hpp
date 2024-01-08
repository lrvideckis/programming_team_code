/** @file */
#pragma once
/**
 * @see https://cp-algorithms.com/string /aho_corasick.html#construction-of-the-trie
 */
const int mn = 'A', max_val = 26; // mn <= s[i] < mn + max_val
struct trie {
    struct node {
        array<int, max_val> next;
        int cnt_words = 0, par = -1;
        char ch;
        node(int _par = -1, char _ch = '#') : par(_par), ch(_ch) {
            fill(begin(next), end(next), -1);
        }
    };
    vector<node> t;
    trie() : t(1) {}
    void insert(const string& s) {
        int u = 0;
        for (char ch : s) {
            int v = ch - mn;
            if (t[u].next[v] == -1) {
                t[u].next[v] = ssize(t);
                t.emplace_back(u, ch);
            }
            u = t[u].next[v];
        }
        t[u].cnt_words++;
    }
    int find(const string& s) {
        int u = 0;
        for (char ch : s) {
            int v = ch - mn;
            if (t[u].next[v] == -1) return 0;
            u = t[u].next[v];
        }
        return t[u].cnt_words;
    }
};
