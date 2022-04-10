//leaks memory
//modified from https://cp-algorithms.com/data_structures/segment_tree.html#preserving-the-history-of-its-values-persistent-segment-tree
//tested on https://www.spoj.com/problems/PSEGTREE/
struct persistentSegTree {
	struct Node {
		Node* lCh, *rCh;//children -> either both null or both exist
		ll sum;
		int l, r; //defines range of node

		Node(int idx, ll val) : lCh(nullptr), rCh(nullptr), sum(val), l(idx), r(idx) {}
		Node(Node* _lCh, Node* _rCh) : lCh(_lCh), rCh(_rCh), sum(lCh->sum + rCh->sum), l(lCh->l), r(rCh->r) {}
	};

	vector<Node*> roots;

	persistentSegTree(const vector<ll>& arr) {
		roots.push_back(build(arr, 0, (int)arr.size() - 1));
	}
	Node* build(const vector<ll>& arr, int tl, int tr) {
		if (tl == tr)
			return new Node(tl, arr[tl]);
		int tm = (tl + tr) / 2;
		return new Node(build(arr, tl, tm), build(arr, tm + 1, tr));
	}

	void update(int version, int pos, int new_val) {
		roots.push_back(update(roots[version], pos, new_val));
	}
	Node* update(Node* v, int pos, int new_val) {
		if (v->l == v->r)
			return new Node(v->l, v->sum + new_val);
		if (pos <= (v->l + v->r) / 2)
			return new Node(update(v->lCh, pos, new_val), v->rCh);
		else
			return new Node(v->lCh, update(v->rCh, pos, new_val));
	}

	ll query(int version, int l, int r) {
		return query(roots[version], l, r);
	}
	ll query(Node* v, int l, int r) {
		if (v->r < l || r < v->l)
			return 0;
		if (l <= v->l && v->r <= r)
			return v->sum;
		return query(v->lCh, l, r) + query(v->rCh, l, r);
	}
};
