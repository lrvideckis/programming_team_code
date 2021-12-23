#pragma once

//modified from k-th smallest section of https://cp-algorithms.com/data_structures/segment_tree.html
struct pst {
public:
	/* Persistent seg tree handle a variety of queries
	 * - no updates. For point updates, use either merge sort tree, wavelet tree or sqrt-decomp
	 * O(nlogn) time and space to build tree
	 */
	pst(const vector<int> &arr) : sorted(arr), n(arr.size()) {
		nodes.reserve(4 * n * log(n + 1));
		roots.reserve(n+1);
		nodes.push_back(Node(Node::Data{0,0}));//acts as nullptr
		sort(sorted.begin(), sorted.end());
		sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
		tl = 0, tr = (int)sorted.size()-1;
		roots.push_back(0);
		for (int val : arr) {
			int idx = lower_bound(sorted.begin(), sorted.end(), val) - sorted.begin();
			roots.push_back(update(roots.back(), tl, tr, idx, val));
		}
	}
	/* find kth smallest number among arr[L], arr[L+1], ..., arr[R]
	 * k is 1-based, so find_kth(L,R,1) returns the min
	 * O(logn)
	 */
	int find_kth(int L, int R, int k) const {
		assert(1 <= k && k <= R-L+1);//note this condition implies L <= R
		assert(0 <= L && R < n);
		return sorted[find_kth(roots[L], roots[R+1], tl, tr, k)];
	}

	/* Among elements arr[L], arr[L+1], ..., arr[R], this returns:
	 * the number of elements which is in range [valueL, valueR]
	 * */
	int cnt_in_range(int L, int R, int valueL, int valueR) const {
		return calc_in_range(L, R, valueL, valueR).cnt;
	}

	/* Among elements arr[L], arr[L+1], ..., arr[R], this returns:
	 * the **sum** of elements which is in range [valueL, valueR]
	 * */
	ll sum_in_range(int L, int R, int valueL, int valueR) const {
		return calc_in_range(L, R, valueL, valueR).sum;
	}

	/* Returns sum of min(arr[i], X) for i in range [L,R]
	 *
	 * assumes -1e9 <= arr[i] <= 1e9 for each i
	 * */
	ll sum_in_range_min(int L, int R, int X) const {
		return calc_in_range(L, R, -1e9, X).sum + 1LL * calc_in_range(L, R, X+1, 1e9).cnt * X;
	}

	/* Returns sum of max(arr[i], X) for i in range [L,R]
	 *
	 * assumes -1e9 <= arr[i] <= 1e9 for each i
	 * */
	ll sum_in_range_max(int L, int R, int X) const {
		return calc_in_range(L, R, X, 1e9).sum + 1LL * calc_in_range(L, R, -1e9, X-1).cnt * X;
	}
private:
	struct Node {
		int lCh, rCh;
		struct Data {
			int cnt;
			ll sum;
		} data;
		Node(Data _data) : lCh(0), rCh(0), data(_data) {}
		Node(int _lCh, int _rCh, const vector<Node>& nodes) : lCh(_lCh), rCh(_rCh), data(combine(nodes[_lCh].data, nodes[_rCh].data)) { }
	};
	static Node::Data combine(const Node::Data& L, const Node::Data& R) {
		return Node::Data {
			L.cnt + R.cnt,
			L.sum + R.sum
		};
	}
	vector<Node> nodes;
	vector<int> roots, sorted;
	int allocateNode(const Node& v) {
		nodes.push_back(v);
		return (int)nodes.size()-1;
	}
	int tl, tr, n;
	int update(int v, int l, int r, int pos, int val) {
		if (l == r) {
			return allocateNode(Node({nodes[v].data.cnt+1, nodes[v].data.sum + val}));
		}
		int m = (l + r) / 2;
		if (pos <= m)
			return allocateNode(Node(update(nodes[v].lCh, l, m, pos, val), nodes[v].rCh, nodes));
		return allocateNode(Node(nodes[v].lCh, update(nodes[v].rCh, m+1, r, pos, val), nodes));
	}
	int find_kth(int vl, int vr, int l, int r, int k) const {
		if (l == r)
			return l;
		int m = (l + r) / 2, left_count = nodes[nodes[vr].lCh].data.cnt - nodes[nodes[vl].lCh].data.cnt;
		if (left_count >= k) return find_kth(nodes[vl].lCh, nodes[vr].lCh, l, m, k);
		return find_kth(nodes[vl].rCh, nodes[vr].rCh, m+1, r, k-left_count);
	}
	Node::Data calc_in_range(int L, int R, int valueL, int valueR) const {
		assert(L <= R && valueL <= valueR);
		int compL = lower_bound(sorted.begin(), sorted.end(), valueL) - sorted.begin();
		int compR = (int)(upper_bound(sorted.begin(), sorted.end(), valueR) - sorted.begin()) - 1;
		if(compL > compR) return {0,0};
		return calc_in_range(roots[L], roots[R+1], tl, tr, compL, compR);
	}
	Node::Data calc_in_range(int vl, int vr, int l, int r, int valueL, int valueR) const {
		if(valueR < l || r < valueL) return {0,0};
		if(valueL <= l && r <= valueR) return {nodes[vr].data.cnt - nodes[vl].data.cnt, nodes[vr].data.sum - nodes[vl].data.sum};
		int m = (l + r) / 2;
		return combine(
			calc_in_range(nodes[vl].lCh, nodes[vr].lCh, l, m, valueL, valueR),
			calc_in_range(nodes[vl].rCh, nodes[vr].rCh, m+1, r, valueL, valueR)
		);
	}
};
