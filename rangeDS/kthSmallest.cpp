//modified from k-th smallest section of https://cp-algorithms.com/data_structures/segment_tree.html
struct persistentSegTree {
	public:
		/* Persistent seg tree to find kth smallest number in a range
		 * - no updates
		 * O(nlogn) time and space to build tree
		 */
		persistentSegTree(const vector<int> &arr) {
			doCompression(arr);
			tl = 0, tr = (int)arr.size();
			roots.push_back(build(tl, tr));
			for (int i = 0; i < (int)arr.size(); i++) {
				roots.push_back(update(roots.back(), tl, tr, compress[i]));
			}
		}
		/* find kth smallest number among arr[L], arr[L+1], ..., arr[R]
		 * k is 1-based, so find_kth(L,R,1) returns the min
		 * O(logn)
		 */
		int find_kth(int L, int R, int k) const {
			assert(1 <= k && k <= R-L+1);
			return sorted[find_kth(roots[L], roots[R+1], tl, tr, k)];
		}
	private:
		vector<int> compress, sorted;
		void doCompression(const vector<int> &arr) {
			int n = arr.size();
			sorted = arr;
			sort(sorted.begin(), sorted.end());
			sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
			compress.resize(n);
			for(int i = 0; i < n; ++i) {
				compress[i] = lower_bound(sorted.begin(), sorted.end(), arr[i]) - sorted.begin();
			}
		}
		struct Vertex {
			Vertex *l, *r;
			int sum;
			Vertex(int val) : l(nullptr), r(nullptr), sum(val) {}
			Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
				if (l) sum += l->sum;
				if (r) sum += r->sum;
			}
		};
		vector<Vertex*> roots;
		int tl,tr;
		Vertex* build(int l, int r) {
			if (l == r)
				return new Vertex(0);
			int m = (l + r) / 2;
			return new Vertex(build(l, m), build(m+1, r));
		}
		Vertex* update(Vertex* v, int l, int r, int pos) {
			if (l == r)
				return new Vertex(v->sum+1);
			int m = (l + r) / 2;
			if (pos <= m)
				return new Vertex(update(v->l, l, m, pos), v->r);
			else
				return new Vertex(v->l, update(v->r, m+1, r, pos));
		}
		int find_kth(Vertex* vl, Vertex *vr, int l, int r, int k) const {
			if (l == r)
				return l;
			int m = (l + r) / 2, left_count = vr->l->sum - vl->l->sum;
			if (left_count >= k) return find_kth(vl->l, vr->l, l, m, k);
			return find_kth(vl->r, vr->r, m+1, r, k-left_count);
		}
};
