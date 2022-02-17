#pragma once

//status: not tested, but used in various problems

struct MergeSortTree {
	struct Node {
		vector<int> vals;
	};
	vector<Node> tree;
	int n, size;

	/*implement these*/
	Node combine(const Node& L, const Node& R) {
		Node par;
		//merge from merge sort
		int ptrL = 0, ptrR = 0;
		while (ptrL < (int) L.vals.size() && ptrR < (int) R.vals.size()) {
			int valL = L.vals[ptrL];
			int valR = R.vals[ptrR];
			if (valL > valR) {
				par.vals.push_back(valR);
				ptrR++;
			} else if (valL < valR) {
				par.vals.push_back(valL);
				ptrL++;
			} else {
				par.vals.push_back(valL);
				par.vals.push_back(valL);
				ptrL++, ptrR++;
			}
		}
		while (ptrL < (int) L.vals.size())
			par.vals.push_back(L.vals[ptrL++]);
		while (ptrR < (int) R.vals.size())
			par.vals.push_back(R.vals[ptrR++]);
		return par;
	}

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
