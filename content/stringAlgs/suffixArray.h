#pragma once

//modified from here: https://judge.yosupo.jp/submission/37410
//
//status: tested on random inputs, and on https://open.kattis.com/problems/automatictrading
class suffix_array {
public:
	//computes suffix array, lcp array, and then sparse table over lcp array
	//O(n log n)
	suffix_array(const string& s) {
		int n = (int)s.size();
		vector<int> arr(n);
		for(int i = 0; i < n; i++) {
			arr[i] = s[i];
		}
		sa_ = sa_is(arr, 255);
		inv_sa_.resize(n);
		for(int i = 0; i < n; i++) {
			inv_sa_[sa_[i]] = i;
		}
		lcp_ = lcp_array(arr, sa_);
		init_min_sparse_table(lcp_);
	}

	//length of longest common prefix of suffixes s[idx1..n], s[idx2..n], 0-based indexing
	//You can check if two substrings s[L1..R1], s[L2..R2] are equal in O(1) by:
	//
	//R2-L2 == R1-L1 && suffix_array::longest_common_prefix(L1, L2) >= R2-L2+1
	int longest_common_prefix(int idx1, int idx2) const {
		if(idx1 == idx2) return (int)sa_.size() - idx1;
		idx1 = inv_sa_[idx1];
		idx2 = inv_sa_[idx2];
		if(idx1 > idx2) swap(idx1, idx2);
		int lg = log2_[idx2-idx1];
		return min(dp_[lg][idx1], dp_[lg][idx2-(1<<lg)]);
	}

	//returns true if suffix s[idx1..n] < s[idx2..n]
	//(so false if idx1 == idx2)
	//O(1)
	bool less(int idx1, int idx2) const {
		return inv_sa_[idx1] < inv_sa_[idx2];
	}

	vector<int> get_suffix_array() const {
		return sa_;
	}

	vector<int> get_lcp_array() const {
		return lcp_;
	}
private:
	vector<int> sa_, lcp_, inv_sa_, log2_;
	vector<vector<int>> dp_;

	// SA-IS, linear-time suffix array construction
	// Reference:
	// G. Nong, S. Zhang, and W. H. Chan,
	// Two Efficient Algorithms for Linear Time Suffix Array Construction
	vector<int> sa_is(const vector<int>& s, int upper) {
		int n = (int)s.size();
		if (n == 0) return {};
		if (n == 1) return {0};
		if (n == 2) {
			if (s[0] < s[1]) {
				return {0, 1};
			} else {
				return {1, 0};
			}
		}

		vector<int> sa(n);
		vector<bool> ls(n);
		for (int i = n - 2; i >= 0; i--) {
			ls[i] = (s[i] == s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]);
		}
		vector<int> sum_l(upper + 1), sum_s(upper + 1);
		for (int i = 0; i < n; i++) {
			if (!ls[i]) {
				sum_s[s[i]]++;
			} else {
				sum_l[s[i] + 1]++;
			}
		}
		for (int i = 0; i <= upper; i++) {
			sum_s[i] += sum_l[i];
			if (i < upper) sum_l[i + 1] += sum_s[i];
		}

		vector<int> buf(upper + 1);
		auto induce = [&](const vector<int>& lms) {
			fill(sa.begin(), sa.end(), -1);
			fill(buf.begin(), buf.end(), 0);
			copy(sum_s.begin(), sum_s.end(), buf.begin());
			for (auto d : lms) {
				if (d == n) continue;
				sa[buf[s[d]]++] = d;
			}
			copy(sum_l.begin(), sum_l.end(), buf.begin());
			sa[buf[s[n - 1]]++] = n - 1;
			for (int i = 0; i < n; i++) {
				int v = sa[i];
				if (v >= 1 && !ls[v - 1]) {
					sa[buf[s[v - 1]]++] = v - 1;
				}
			}
			copy(sum_l.begin(), sum_l.end(), buf.begin());
			for (int i = n - 1; i >= 0; i--) {
				int v = sa[i];
				if (v >= 1 && ls[v - 1]) {
					sa[--buf[s[v - 1] + 1]] = v - 1;
				}
			}
		};

		vector<int> lms_map(n + 1, -1);
		int m = 0;
		for (int i = 1; i < n; i++) {
			if (!ls[i - 1] && ls[i]) {
				lms_map[i] = m++;
			}
		}
		vector<int> lms;
		lms.reserve(m);
		for (int i = 1; i < n; i++) {
			if (!ls[i - 1] && ls[i]) {
				lms.push_back(i);
			}
		}

		induce(lms);

		if (m) {
			vector<int> sorted_lms;
			sorted_lms.reserve(m);
			for (int v : sa) {
				if (lms_map[v] != -1) sorted_lms.push_back(v);
			}
			vector<int> rec_s(m);
			int rec_upper = 0;
			rec_s[lms_map[sorted_lms[0]]] = 0;
			for (int i = 1; i < m; i++) {
				int l = sorted_lms[i - 1], r = sorted_lms[i];
				int end_l = (lms_map[l] + 1 < m) ? lms[lms_map[l] + 1] : n;
				int end_r = (lms_map[r] + 1 < m) ? lms[lms_map[r] + 1] : n;
				bool same = true;
				if (end_l - l != end_r - r) {
					same = false;
				} else {
					while (l < end_l) {
						if (s[l] != s[r]) {
							break;
						}
						l++;
						r++;
					}
					if (l == n || s[l] != s[r]) same = false;
				}
				if (!same) rec_upper++;
				rec_s[lms_map[sorted_lms[i]]] = rec_upper;
			}

			auto rec_sa =
				sa_is(rec_s, rec_upper);

			for (int i = 0; i < m; i++) {
				sorted_lms[i] = lms[rec_sa[i]];
			}
			induce(sorted_lms);
		}
		return sa;
	}

	// Reference:
	// T. Kasai, G. Lee, H. Arimura, S. Arikawa, and K. Park,
	// Linear-Time Longest-Common-Prefix Computation in Suffix Arrays and Its
	// Applications
	vector<int> lcp_array(const vector<int>& s, const vector<int>& sa) {
		int n=s.size(),k=0;
		vector<int> lcp(n,0);
		vector<int> rank(n,0);
		for(int i=0; i<n; i++) rank[sa[i]]=i;
		for(int i=0; i<n; i++, k?k--:0) {
			if(rank[i]==n-1) {
				k=0;
				continue;
			}
			int j=sa[rank[i]+1];
			while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
			lcp[rank[i]]=k;
		}
		return lcp;
	}

	void init_min_sparse_table(const vector<int>& arr) {
		const int n = arr.size();
		log2_.resize(n+1,-1);
		for(int i = 1; i <= n; ++i) log2_[i] = 1 + log2_[i/2];
		dp_.resize(log2_[n] + 1, arr);
		for(int i = 1; i <= log2_[n]; ++i) {
			for(int j = 0; j+(1<<i)-1<n; ++j) {
				dp_[i][j] = min(dp_[i-1][j], dp_[i-1][j+(1<<(i-1))]);
			}
		}
	}
};
