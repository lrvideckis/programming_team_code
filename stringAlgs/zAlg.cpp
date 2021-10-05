//z[i] is the length of the longest substring
//starting from s[i] which is also a prefix of s
//stolen from https://cp-algorithms.com/string/z-function.html
vector<int> z_function(const string &s) {
	int n = (int) s.length();
	vector<int> z(n);
	for (int i = 1, l = 0, r = 0; i < n; ++i) {
		if (i <= r)
			z[i] = min (r - i + 1, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			++z[i];
		if (i + z[i] - 1 > r)
			l = i, r = i + z[i] - 1;
	}
	z[0] = n;
	return z;
}
