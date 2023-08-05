#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"

#include "../../../library/strings/suffix_array_related/find_substrs_concatenated.hpp"
#include "../../../library/strings/suffix_array_related/substr_cmp.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int n = 0; n <= 30; n++) {
        for (int tests = 10; tests--;) {
            string s(n, 'a');
            int mx_char = get_rand<int>(0, 5);
            generate(begin(s), end(s), [&]() {return char('a' + get_rand<int>(0, mx_char));});
            lcp_query lq(s, 256);
            for (int str_le = 0; str_le <= n; str_le++) {
                for (int str_ri = str_le; str_ri <= n; str_ri++) {
                    auto [le, ri] = find_substrs_concated(s, lq, {{str_le, str_ri}});
                    if (str_le == str_ri)
                        assert(le == 0 && ri == n);
                    if (str_le < n)
                        assert(0 <= le && le <= lq.sf.sa_inv[str_le] && lq.sf.sa_inv[str_le] < ri && ri <= n);
                    for (int i = le; i < ri; i++)
                        assert(s.substr(lq.sf.sa[i], str_ri - str_le) == s.substr(str_le, str_ri - str_le));
                    assert(le == 0 || s.substr(lq.sf.sa[le - 1], str_ri - str_le) != s.substr(str_le, str_ri - str_le));
                    assert(ri == n || s.substr(lq.sf.sa[ri], str_ri - str_le) != s.substr(str_le, str_ri - str_le));
                }
            }
            for (int i = 0; i <= n; i++) {
                for (int j = i; j <= n; j++) {
                    for (int k = 0; k <= n; k++) {
                        for (int l = k; l <= n; l++) {
                            int cmp_val = substr_cmp(lq, i, j, k, l);
                            string sub1 = s.substr(i, j - i);
                            string sub2 = s.substr(k, l - k);
                            if (cmp_val < 0) assert(sub1 < sub2);
                            if (cmp_val == 0) assert(sub1 == sub2);
                            if (cmp_val > 0) assert(sub1 > sub2);
                        }
                    }
                }
            }
        }
    }
    cout << "Hello World\n";
    return 0;
}
