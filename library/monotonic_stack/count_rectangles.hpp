/**
 * @code{.cpp}
       vector<long long> a;
       auto ri = mono_st(a, less()); // greater(), less_equal(), greater_equal()
       for (int i = n - 1; i >= 0; i--)
           for (int j = i + 1; j != ri[i]; j = ri[j])
               // for all k in [j, ri[j]): cmp(a[i], a[k])
               // these ranges are disjoint, and union to [i + 1, ri[i])
 * @endcode
 * @param a array
 * @param cmp any transitive compare operator
 * @returns array ri where ri[i] = max integer such that:
 *     for all k in [i + 1, ri[i]): cmp(a[i], a[k])
 * @time O(n)
 * @space a O(n) vector is allocated and returned
 */
template <class T, class F> vector<int> mono_st(const vector<T>& a, F cmp) {
	vector<int> ri(ssize(a));
	for (int i = ssize(a) - 1; i >= 0; i--)
		for (ri[i] = i + 1; ri[i] < ssize(a) && cmp(a[i], a[ri[i]]);) ri[i] = ri[ri[i]];
	return ri;
}
/**
 * @code{.cpp}
       vector<long long> a;
       auto ri = mono_st(a, less()), le = mono_range(ri); // greater(), less_equal(), greater_equal()
 * @endcode
 * @param ri monotonic stack array of a
 * @returns (if you use less()) vector le such that:
 *     - le[i] < i < ri[i]
 *     - a[i] is the min of exclusive-exclusive range (le[i], ri[i])
 *     - le[i] is the max index such that a[le[i]] < a[i], or -1
 *     - ri[i] is the min index such that a[i] >= a[ri[i]], or n
 * @time O(n)
 * @space two O(n) vectors are allocated and returned
 */
vector<int> mono_range(const vector<int>& ri) {
	vector le(ssize(ri), -1);
	for (int i = 0; i < ssize(ri); i++)
		for (int j = i + 1; j != ri[i]; j = ri[j]) le[j] = i;
	return le;
}
/**
 * @param grid an n-by-m boolean array
 * @returns an (n+1)-by-(m+1) array cnt where cnt[i][j] = the number of times
 * an i-by-j sub rectangle appears in the matrix such that all i*j cells in the
 * sub rectangle are 1. cnt[i][0] and cnt[0][j] will contain garbage values.
 * @time O(n * m)
 * @space this function allocates/returns a O(n * m) vector
 */
vector<vector<int>> count_rectangles(const vector<vector<bool>>& grid) {
	int n = ssize(grid), m = ssize(grid[0]);
	vector cnt(n + 1, vector(m + 1, 0));
	vector<int> h(m);
	for (const auto& row : grid) {
		transform(begin(h), end(h), begin(row), begin(h), [](int a, bool g) {
			return g * (a + 1);
		});
		auto ri = mono_st(h, less()), le = mono_range(ri);
		for (int j = 0; j < m; j++) {
			int cnt_l = j - le[j] - 1, cnt_r = ri[j] - j - 1;
			cnt[h[j]][cnt_l + cnt_r + 1]++;
			cnt[h[j]][cnt_l]--;
			cnt[h[j]][cnt_r]--;
		}
	}
	for (int i = 1; i <= n; i++)
		for (int k = 0; k < 2; k++)
			for (int j = m; j > 1; j--)
				cnt[i][j - 1] += cnt[i][j];
	for (int i = n; i > 1; i--)
		for (int j = 1; j <= m; j++)
			cnt[i - 1][j] += cnt[i][j];
	return cnt;
}
