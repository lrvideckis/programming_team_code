#pragma once
/**
 * @see https://cp-algorithms.com/string/prefix-function.html#implementation
 * @time O(n)
 */
template <typename T> vector<int> prefix_function(const T& s) {
	vector<int> pi(ssize(s), 0);
	transform(pi.begin(), pi.end() - 1, s.begin() + 1, pi.begin() + 1, [&](int j, auto val) {
		while (j > 0 && val != s[j]) j = pi[j - 1];
		return j + (val == s[j]);
	});
	return pi;
}
