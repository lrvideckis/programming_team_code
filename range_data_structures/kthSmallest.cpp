//modified from k-th smallest section of https://cp-algorithms.com/data_structures/segment_tree.html
struct kthSmallest {
public:
	/* Persistent seg tree to find kth smallest number in a range
	 * - no updates
	 * O(nlogn) time and space to build tree
	 */
	kthSmallest(const vector<int> &arr) {
		tl = *min_element(arr.begin(), arr.end());
		tr = *max_element(arr.begin(), arr.end());
		roots.push_back(shared_ptr<Vertex>(new Vertex(0)));
		for (int val : arr) {
			roots.push_back(update(roots.back(), tl, tr, val));
		}
	}
	/* find kth smallest number among arr[L], arr[L+1], ..., arr[R]
	 * k is 1-based, so find_kth(L,R,1) returns the min
	 * O(logn)
	 */
	int find_kth(int L, int R, int k) const {
		assert(1 <= k && k <= R-L+1);
		return find_kth(roots[L], roots[R+1], tl, tr, k);
	}
	/* does: arr[idx] = newValue
	 *
	 */
	void update(int idx, int newValue) {

	}
private:
	struct Vertex {
		shared_ptr<Vertex> l, r;
		int sum;
		Vertex(int val) : l(nullptr), r(nullptr), sum(val) {}
		Vertex(shared_ptr<Vertex> _l, shared_ptr<Vertex> _r) : l(_l), r(_r), sum(0) {
			if (l) sum += l->sum;
			if (r) sum += r->sum;
		}
		static int getSum(shared_ptr<Vertex> v) {
			return v ? v->sum : 0;
		}
		static shared_ptr<Vertex> getL(shared_ptr<Vertex> v) {
			return v ? v->l : nullptr;
		}
		static shared_ptr<Vertex> getR(shared_ptr<Vertex> v) {
			return v ? v->r : nullptr;
		}
	};
	vector<shared_ptr<Vertex>> roots;
	int tl,tr;
	int getMid(int l, int r) const {
		int mid = l + (r - l)/2;
		if(mid > l) mid--;
		return mid;
	}
	shared_ptr<Vertex> update(shared_ptr<Vertex> v, int l, int r, int pos) {
		if (l == r)
			return shared_ptr<Vertex>(new Vertex(Vertex::getSum(v)+1));
		int m = getMid(l, r);
		if (pos <= m)
			return shared_ptr<Vertex>(new Vertex(update(Vertex::getL(v), l, m, pos), Vertex::getR(v)));
		else
			return shared_ptr<Vertex>(new Vertex(Vertex::getL(v), update(Vertex::getR(v), m+1, r, pos)));
	}
	int find_kth(shared_ptr<Vertex> vl, shared_ptr<Vertex> vr, int l, int r, int k) const {
		if (l == r)
			return l;
		int m = getMid(l, r), left_count = Vertex::getSum(Vertex::getL(vr)) - Vertex::getSum(Vertex::getL(vl));
		if (left_count >= k) return find_kth(Vertex::getL(vl), Vertex::getL(vr), l, m, k);
		return find_kth(Vertex::getR(vl), Vertex::getR(vr), m+1, r, k-left_count);
	}
};
