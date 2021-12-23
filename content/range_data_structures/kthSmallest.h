#pragma once

//modified from k-th smallest section of https://cp-algorithms.com/data_structures/segment_tree.html
struct kthSmallest {
public:
	/* Persistent seg tree to find kth smallest number in a range
	 * - no updates
	 * O(nlogn) time and space to build tree
	 */
	kthSmallest(const vector<int> &arr) : sorted(arr), n(arr.size()) {
		nodes.reserve(4 * n * log(n + 1));
		roots.reserve(n+1);
		nodes.push_back(Node(0));//acts as nullptr
		sort(sorted.begin(), sorted.end());
		sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
		tl = 0, tr = (int)sorted.size()-1;
		roots.push_back(0);
		for (int val : arr) {
			int idx = lower_bound(sorted.begin(), sorted.end(), val) - sorted.begin();
			roots.push_back(update(roots.back(), tl, tr, idx));
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
		assert(L <= R && valueL <= valueR);
		int compL = lower_bound(sorted.begin(), sorted.end(), valueL) - sorted.begin();
		int compR = (int)(upper_bound(sorted.begin(), sorted.end(), valueR) - sorted.begin()) - 1;
		if(compL > compR) return 0;
		return cnt_in_range(roots[L], roots[R+1], tl, tr, compL, compR);
	}

	/* Among elements arr[L], arr[L+1], ..., arr[R], this returns:
	 * the **sum** of elements which is in range [valueL, valueR]
	 * */
	int sum_in_range(int L, int R, int valueL, int valueR) const {
		//TODO
		assert(false);
	}

private:
	struct Node {
		int l, r;
		int cnt;
		Node(int _cnt) : l(0), r(0), cnt(_cnt) {}
		Node(int _l, int _r, const vector<Node>& nodes) : l(_l), r(_r), cnt(nodes[_l].cnt + nodes[_r].cnt) { }
	};
	vector<Node> nodes;
	vector<int> roots, sorted;
	int allocateNode(const Node& v) {
		nodes.push_back(v);
		return (int)nodes.size()-1;
	}
	int tl, tr, n;
	int update(int v, int l, int r, int pos) {
		if (l == r) {
			return allocateNode(Node(nodes[v].cnt+1));
		}
		int m = (l + r) / 2;
		if (pos <= m)
			return allocateNode(Node(update(nodes[v].l, l, m, pos), nodes[v].r, nodes));
		return allocateNode(Node(nodes[v].l, update(nodes[v].r, m+1, r, pos), nodes));
	}
	int find_kth(int vl, int vr, int l, int r, int k) const {
		if (l == r)
			return l;
		int m = (l + r) / 2, left_count = nodes[nodes[vr].l].cnt - nodes[nodes[vl].l].cnt;
		if (left_count >= k) return find_kth(nodes[vl].l, nodes[vr].l, l, m, k);
		return find_kth(nodes[vl].r, nodes[vr].r, m+1, r, k-left_count);
	}
	int cnt_in_range(int vl, int vr, int l, int r, int valueL, int valueR) const {
		if(valueR < l || r < valueL) return 0;
		if(valueL <= l && r <= valueR) return nodes[vr].cnt - nodes[vl].cnt;
		int m = (l + r) / 2;
		return
			cnt_in_range(nodes[vl].l, nodes[vr].l, l, m, valueL, valueR) +
			cnt_in_range(nodes[vl].r, nodes[vr].r, m+1, r, valueL, valueR);
	}
};
