//modified from k-th smallest section of https://cp-algorithms.com/data_structures/segment_tree.html
struct kthSmallest {
public:
	/* Persistent seg tree to find kth smallest number in a range
	 * - no updates
	 * O(nlogn) time and space to build tree
	 */
	kthSmallest(const vector<int> &arr) {
		doCompression(arr);
		tl = 0, tr = (int)sorted.size()-1, n = arr.size();
		roots.push_back(allocateNode(Vertex(0)));
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
	vector<int> sorted;
	void doCompression(const vector<int> &arr) {
		sorted = arr;
		sort(sorted.begin(), sorted.end());
		sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
	}
	struct Vertex {
		int l, r;
		int sum;
		Vertex(int val) : l(-1), r(-1), sum(val) {}
		Vertex(int _l, int _r, const vector<Vertex>& nodes) : l(_l), r(_r), sum(0) {
			if (l != -1) sum += nodes[l].sum;
			if (r != -1) sum += nodes[r].sum;
		}
		static int getSum(int v, const vector<Vertex>& nodes) {
			return v != -1 ? nodes[v].sum : 0;
		}
		static int getL(int v, const vector<Vertex>& nodes) {
			return v != -1 ? nodes[v].l : -1;
		}
		static int getR(int v, const vector<Vertex>& nodes) {
			return v != -1 ? nodes[v].r : -1;
		}
	};
	vector<Vertex> nodes;
	vector<int> roots;
	int allocateNode(Vertex v) {
		int idx = nodes.size();
		nodes.push_back(v);
		return idx;
	}
	int tl, tr, n;
	int update(int v, int l, int r, int pos) {
		if (l == r) {
			return allocateNode(Vertex(Vertex::getSum(v, nodes)+1));
		}
		int m = (l + r) / 2;
		if (pos <= m)
			return allocateNode(Vertex(update(Vertex::getL(v, nodes), l, m, pos), Vertex::getR(v, nodes), nodes));
		return allocateNode(Vertex(Vertex::getL(v, nodes), update(Vertex::getR(v, nodes), m+1, r, pos), nodes));
	}
	int find_kth(int vl, int vr, int l, int r, int k) const {
		if (l == r)
			return l;
		int m = (l + r) / 2, left_count = Vertex::getSum(Vertex::getL(vr, nodes), nodes) - Vertex::getSum(Vertex::getL(vl, nodes), nodes);
		if (left_count >= k) return find_kth(Vertex::getL(vl, nodes), Vertex::getL(vr, nodes), l, m, k);
		return find_kth(Vertex::getR(vl, nodes), Vertex::getR(vr, nodes), m+1, r, k-left_count);
	}
};
