//modified from k-th smallest section of https://cp-algorithms.com/data_structures/segment_tree.html
struct kthSmallest {
public:
	/* Persistent seg tree to find kth smallest number in a range
	 * - no updates
	 * O(nlogn) time and space to build tree
	 */
	kthSmallest(const vector<int> &arr) : sorted(arr) {
		nodes.push_back(Node(0));//acts as nullptr
		sort(sorted.begin(), sorted.end());
		sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
		tl = 0, tr = (int)sorted.size()-1, n = arr.size();
		roots.push_back(allocateNode(Node(0)));
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
		assert(1 <= k && k <= R-L+1);
		assert(0 <= L && R < n);
		return sorted[find_kth(roots[L], roots[R+1], tl, tr, k)];
	}
private:
	struct Node {
		int l, r;
		int sum;
		Node(int val) : l(0), r(0), sum(val) {}
		Node(int _l, int _r, const vector<Node>& nodes) : l(_l), r(_r), sum(nodes[_l].sum + nodes[_r].sum) { }
	};
	vector<Node> nodes;
	vector<int> roots, sorted;
	int allocateNode(const Node& v) {
		int idx = nodes.size();
		nodes.push_back(v);
		return idx;
	}
	int tl, tr, n;
	int update(int v, int l, int r, int pos) {
		if (l == r) {
			return allocateNode(Node(nodes[v].sum+1));
		}
		int m = (l + r) / 2;
		if (pos <= m)
			return allocateNode(Node(update(nodes[v].l, l, m, pos), nodes[v].r, nodes));
		return allocateNode(Node(nodes[v].l, update(nodes[v].r, m+1, r, pos), nodes));
	}
	int find_kth(int vl, int vr, int l, int r, int k) const {
		if (l == r)
			return l;
		int m = (l + r) / 2, left_count = nodes[nodes[vr].l].sum - nodes[nodes[vl].l].sum;
		if (left_count >= k) return find_kth(nodes[vl].l, nodes[vr].l, l, m, k);
		return find_kth(nodes[vl].r, nodes[vr].r, m+1, r, k-left_count);
	}
};
