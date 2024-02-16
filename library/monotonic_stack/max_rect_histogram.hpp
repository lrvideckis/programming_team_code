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
 * @param a contains positive integers
 * @returns largest integer x such that there exists a subarray a[le,ri)
 * with: (ri-le) * min(a[le,ri)) == x
 * @time O(n)
 * @space besides O(n) param `a`, O(n) extra space is allocated temporarily
 */
long long max_rect_histogram(const vector<int>& a) {
	auto ri = mono_st(a, less()), le = mono_range(ri);
	auto max_area = 0LL;
	for (int i = 0; i < ssize(a); i++)
		max_area = max(max_area, 1LL * a[i] * (ri[i] - le[i] - 1));
	return max_area;
}
