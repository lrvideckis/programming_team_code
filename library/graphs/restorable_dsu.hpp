//https://github.com/ucf-programming-team/hackpack-cpp/blob/master/content/data-structures/DSURestorable.h
struct RestorableDSU {
	vector<int> s, times;
	vector<pair<int, int>> stk;
	RestorableDSU(int n): s(n, -1) {}
	int find(int i) const { return s[i] < 0 ? i : find(s[i]); }
	bool update(int a, int b) {
		times.push_back(ssize(stk));
		a = find(a), b = find(b);
		if (a == b) return false;
		if (s[a] > s[b]) swap(a, b);
		stk.emplace_back(a, s[a]);
		stk.emplace_back(b, s[b]);
		s[a] += s[b], s[b] = a;
		return true;
	}
	void undo() {
		assert(!times.empty());
		while (ssize(stk) > times.back())
			s[stk.back().first] = stk.back().second, stk.pop_back();
		times.pop_back();
	}
	int size(int i) const { return -s[find(i)]; }
	bool same(int a, int b) const { return find(a) == find(b); }
};
