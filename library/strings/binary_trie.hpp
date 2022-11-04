#pragma once
struct binary_trie {
	const int MX_BIT = 62;
	struct node {
		long long val = -1;
		int sub_sz = 0;//number of inserted values in subtree
		array<int, 2> next = {-1, -1};
	};
	vector<node> t;
	binary_trie() : t(1) {}
	/**
	 * Pass delta = 1 to insert val, -1 to remove val, 0 to get the # of val's
	 * in this data structure.
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
	int size() const {
		return t[0].sub_sz;
	}
	/**
	 * Returns x such that x is in this data structure, and the value of
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
