/** @file */
#pragma once
/**
 * @see https://cp-algorithms.com/string/ aho_corasick.html#construction-of-the-trie
 */
const int K = 26; /**< alphabet size */
struct trie {
	const char MIN_CH = 'A'; /**< 'a' for lowercase, '0' for digits */
	struct node {
		int next[K], cnt_words = 0, par = -1;
		char ch;
		node(int a_par = -1, char a_ch = '#') : par(a_par), ch(a_ch) {
			fill(next, next + K, -1);
		}
	};
	vector<node> t;
	trie() : t(1) {}
	void insert(const string& s) {
		int v = 0;
		for (auto ch : s) {
			int let = ch - MIN_CH;
			if (t[v].next[let] == -1) {
				t[v].next[let] = ssize(t);
				t.emplace_back(v, ch);
			}
			v = t[v].next[let];
		}
		t[v].cnt_words++;
	}
	int find(const string& s) const {
		int v = 0;
		for (auto ch : s) {
			int let = ch - MIN_CH;
			if (t[v].next[let] == -1) return 0;
			v = t[v].next[let];
		}
		return t[v].cnt_words;
	}
};
