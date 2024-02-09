#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"

#include "../../../library/strings/suffix_array_related/find/find_substrings_concatenated.hpp"
#include "../../../library/strings/suffix_array_related/compare/compare_substrings.hpp"
#include "../../../library/strings/suffix_array_related/compare/compare_suffixes.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	for (int n = 0; n <= 30; n++) {
		for (int tests = 10; tests--;) {
			string s(n, 'a');
			int mx_char = get_rand<int>(0, 5);
			generate(begin(s), end(s), [&]() {return char('a' + get_rand<int>(0, mx_char));});
			lcp_query lq(s, 256);
			for (int i = 0; i <= n; i++) {
				for (int j = i; j <= n; j++) {
					auto [sa_le, sa_ri, str_le, str_ri] = find_substrs_concated(lq, {{i, j}});
					assert(s.substr(i, j - i) == s.substr(str_le, str_ri - str_le));
					if (i == j) {
						assert(sa_le == 0 && sa_ri == n);
						assert(str_le == str_ri);
					}
					if (i < n)
						assert(0 <= sa_le && sa_le <= lq.sa_inv[i] && lq.sa_inv[i] < sa_ri && sa_ri <= n);
					for (int idx = sa_le; idx < sa_ri; idx++)
						assert(s.substr(lq.sa[idx], j - i) == s.substr(i, j - i));
					assert(sa_le == 0 || s.substr(lq.sa[sa_le - 1], j - i) != s.substr(i, j - i));
					assert(sa_ri == n || s.substr(lq.sa[sa_ri], j - i) != s.substr(i, j - i));
				}
			}
			for (int i = 0; i <= n; i++) {
				for (int k = 0; k <= n; k++) {
					for (int j = i; j <= n; j++) {
						for (int l = k; l <= n; l++) {
							int cmp_val = substr_cmp(lq, i, j, k, l);
							string sub1 = s.substr(i, j - i);
							string sub2 = s.substr(k, l - k);
							if (cmp_val < 0) assert(sub1 < sub2);
							if (cmp_val == 0) assert(sub1 == sub2);
							if (cmp_val > 0) assert(sub1 > sub2);
						}
					}
					string suf1 = s.substr(i);
					string suf2 = s.substr(k);
					int cmp_val = suf_cmp(lq.sa_inv, i, k);
					if (cmp_val < 0) assert(suf1 < suf2);
					if (cmp_val == 0) assert(suf1 == suf2);
					if (cmp_val > 0) assert(suf1 > suf2);
				}
			}
		}
	}
	cout << "Hello World\n";
	return 0;
}
