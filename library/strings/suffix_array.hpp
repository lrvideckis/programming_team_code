#pragma once
//source: https://judge.yosupo.jp/submission/63467
//time: O(n + alph)
template <typename T> vector<int> suffix_array(const T& s, int alph) {
	int n = ssize(s);
	if (n <= 1)
		return vector<int>(n, 0);
	if (n == 2)
		return {(s[0] >= s[1]), (s[0] < s[1])};
	vector<int> sa(n, 0), is_s(n, 0);
	for (int i = n - 2; i >= 0; i--)
		is_s[i] = (s[i] < s[i + 1] || (s[i] == s[i + 1] && is_s[i + 1]));
	vector<int> head(alph + 1, 0), tail(alph + 1, 0);
	for (int i = 0; i < n; i++)
		++head[s[i] + 1], tail[s[i]] += !is_s[i];
	partial_sum(head.begin(), head.end(), head.begin());
	for (int i = 0; i <= alph; i++)
		tail[i] += head[i];
	vector<int> tmp(alph + 1, 0);
	auto induce = [&](const vector<int>& lms) {
		fill(sa.begin(), sa.end(), -1);
		copy(tail.begin(), tail.end(), tmp.begin());
		for (int i : lms)
			sa[tmp[s[i]]++] = i;
		copy(head.begin(), head.end(), tmp.begin());
		sa[tmp[s[n - 1]]++] = n - 1;
		for (int i = 0; i < n; i++)
			if (int j = sa[i]; j > 0 && !is_s[j - 1])
				sa[tmp[s[j - 1]]++] = j - 1;
		copy(head.begin(), head.end(), tmp.begin());
		for (int i = n - 1; i >= 0; i--)
			if (int j = sa[i]; j > 0 && is_s[j - 1])
				sa[--tmp[s[j - 1] + 1]] = j - 1;
	};
	vector<int> lms_idx(n, -1), lms(0, 0);
	for (int i = 1; i < n; i++)
		if (is_s[i] && !is_s[i - 1])
			lms_idx[i] = ssize(lms), lms.push_back(i);
	induce(lms);
	if (ssize(lms)) {
		vector<int> s2(ssize(lms), 0), sorted_lms;
		copy_if(sa.begin(), sa.end(), back_inserter(sorted_lms), [&](int i) -> bool {
			return lms_idx[i] != -1;
		});
		int alph2 = 0;
		for (int i = 1; i < ssize(lms); i++) {
			int a = sorted_lms[i - 1], b = sorted_lms[i];
			alph2 += !equal(s.begin() + a, s.begin() + (lms_idx[a] + 1 == ssize(lms) ? n : lms[lms_idx[a] + 1]),
							s.begin() + b, s.begin() + (lms_idx[b] + 1 == ssize(lms) ? n : lms[lms_idx[b] + 1]));
			s2[lms_idx[b]] = alph2;
		}
		auto sa2 = suffix_array(s2, alph2 + 1);
		for (int i = 0; i < ssize(lms); i++)
			sorted_lms[i] = lms[sa2[i]];
		induce(sorted_lms);
	}
	return sa;
}
