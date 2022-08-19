#pragma once
//source: https://cp-algorithms.com/string/aho_corasick.html#construction-of-the-trie
//intended to be a base template and to be modified
const int K = 26;//alphabet size
struct trie {
	const char MIN_CH = 'a';//'A' for uppercase, '0' for digits
	struct node {
		int next[K], id, p = -1;
		char ch;
		bool leaf = 0;
		node(int a_p = -1, char a_ch = '#') : p(a_p), ch(a_ch) {
			fill(next, next + K, -1);
		}
	};
	vector<node> t;
	trie() : t(1) {}
	void add_string(const string& s, int id) {
		int c = 0;
		for (char ch : s) {
			int v = ch - MIN_CH;
			if (t[c].next[v] == -1) {
				t[c].next[v] = t.size();
				t.emplace_back(c, ch);
			}
			c = t[c].next[v];
		}
		t[c].leaf = 1;
		t[c].id = id;
	}
	void remove_string(const string& s) {
		int c = 0;
		for (char ch : s) {
			int v = ch - MIN_CH;
			if (t[c].next[v] == -1)
				return;
			c = t[c].next[v];
		}
		t[c].leaf = 0;
	}
	int find_string(const string& s) const {
		int c = 0;
		for (char ch : s) {
			int v = ch - MIN_CH;
			if (t[c].next[v] == -1)
				return -1;
			c = t[c].next[v];
		}
		if (!t[c].leaf) return -1;
		return t[c].id;
	}
};
