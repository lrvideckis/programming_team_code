#pragma once

//status: stress-tested against persistent seg tree; used in various problems

struct MergeSortTree {
	struct Node {
		vector<int> vals;
	};
	vector<Node> tree;
	int n, size;

	/*implement these*/
	Node combine(const Node& L, const Node& R) {
		vector<int> par(L.vals.size() + R.vals.size());
		merge(L.vals.begin(), L.vals.end(), R.vals.begin(), R.vals.end(), par.begin());
		return Node{par};
	}

	//O(nlogn) time and space
	MergeSortTree(const vector<int>& arr) : n((int) arr.size()) {
		size = 1;
		while (size < n) size <<= 1;
		size <<= 1;
		tree.resize(size);
		build(arr, 1, 0, n - 1);
	}
	void build(const vector<int>& arr, int node, int start, int end) {
		if (start == end)
			tree[node].vals.push_back(arr[start]);
		else {
			int mid = (start + end) / 2;
			build(arr, 2 * node, start, mid);
			build(arr, 2 * node + 1, mid + 1, end);
			tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
		}
	}
	//returns how many values of arr[l], arr[l+1], ..., arr[r] which are < x
	//O(log^2)
	int query(int l, int r, int x) {
		return query(1, 0, n - 1, l, r, x);
	}
	int query(int node, int start, int end, int l, int r, int x) {
		if (r < start || end < l) return 0;
		if (l <= start && end <= r) {
			auto& v = tree[node].vals;
			return lower_bound(v.begin(), v.end(), x) - v.begin();
		}
		int mid = (start + end) / 2;
		return query(2 * node, start, mid, l, r, x) + query(2 * node + 1, mid + 1, end, l, r, x);
	}
};
