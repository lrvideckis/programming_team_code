#pragma once
//library checker tests: https://judge.yosupo.jp/problem/set_xor_min
struct binary_trie {
	const int mx_bit = 62;
	struct node {
		long long val = -1;
		int sub_sz = 0;//number of inserted values in subtree
		int next[2] = {-1, -1};
	};
	vector<node> t;
	binary_trie() : t(1) {}
	//delta = 1 to insert val, -1 to remove val
	void update(long long val, int delta) {
		int c = 0;
		t[0].sub_sz += delta;
		for (int bit = mx_bit; bit >= 0; bit--) {
			bool v = (val >> bit) & 1;
			if (t[c].next[v] == -1) {
				t[c].next[v] = t.size();
				t.emplace_back();
			}
			c = t[c].next[v];
			t[c].sub_sz += delta;
		}
		t[c].val = val;
	}
	//returns # of val's in this data structure
	int cnt(long long val) const {
		int c = 0;
		for (int bit = mx_bit; bit >= 0; bit--) {
			bool v = (val >> bit) & 1;
			if (t[c].next[v] == -1)
				return 0;
			c = t[c].next[v];
		}
		return t[c].sub_sz;
	}
	int size() const {
		return t[0].sub_sz;
	}
	//returns x such that:
	//	x is in this data structure
	//	value of (x ^ val) is minimum
	long long min_xor(long long val) const {
		assert(size() > 0);
		int c = 0;
		for (int bit = mx_bit; bit >= 0; bit--) {
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
