/**
 * @code{.cpp}
       vector<long long> a;
       RMQ rmq(a, ranges::min); // -std=c++20
       RMQ rmq(a, [&](auto& x, auto& y) { return min(x, y); });
 * @endcode
 */
template <class T, class F> struct RMQ {
	vector<vector<T>> dp;
	F op;
	RMQ() {}
	/**
	 * @param a static array
	 * @param a_op any associative, communative, idempotent operation
	 * @time O(n log n)
	 * @space O(n log n) for `dp` vector
	 */
	RMQ(const vector<T>& a, F a_op) : dp(1, a), op(a_op) {
		for (int i = 0; (2 << i) <= ssize(a); i++) {
			dp.emplace_back(ssize(a) - (2 << i) + 1);
			transform(begin(dp[i]), end(dp[i]) - (1 << i), begin(dp[i]) + (1 << i), begin(dp[i + 1]), op);
		}
	}
	/**
	 * @param le,ri defines range [le, ri)
	 * @returns a[le] op a[le + 1] op ... op a[ri - 1]
	 * @time O(1)
	 * @space O(1)
	 */
	inline T query(int le, int ri) {
		assert(0 <= le && le < ri && ri <= ssize(dp[0]));
		int lg = __lg(ri - le);
		return op(dp[lg][le], dp[lg][ri - (1 << lg)]);
	}
};
/**
 * @see https://github.com/kth-competitive-programming /kactl/blob/main/content/graph/LCA.h
 */
struct LCA {
	int n;
	vector<int> in, sub_sz, d, p, order;
	RMQ<int, function<int(int, int)>> rmq;
	/**
	 * @param adj forest (rooted or unrooted)
	 * @time O(n log n)
	 * @space O(n log n) for rmq, all other vectors are O(n)
	 */
	LCA(const vector<vector<int>>& adj) : n(ssize(adj)), in(n), sub_sz(n, 1), d(n), p(n, -1) {
		order.reserve(n);
		for (int i = 0; i < n; i++)
			if (p[i] == -1) dfs(adj, i);
		rmq = {order, [&](int u, int v) {return d[u] < d[v] ? u : v;}};
	}
	void dfs(const vector<vector<int>>& adj, int u) {
		in[u] = ssize(order), order.push_back(u);
		for (int v : adj[u])
			if (v != p[u])
				d[v] = d[p[v] = u] + 1, dfs(adj, v), sub_sz[u] += sub_sz[v];
	}
	/**
	 * @param u,v 2 nodes in the same component
	 * @returns lca of u, v
	 * @time O(1)
	 * @space O(1)
	 */
	inline int get_lca(int u, int v) {
		if (u == v) return u;
		auto [x, y] = minmax(in[u], in[v]);
		return p[rmq.query(x + 1, y + 1)];
	}
};
