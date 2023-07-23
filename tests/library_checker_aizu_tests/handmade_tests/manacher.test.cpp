#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"

#include "../../../library/strings/manacher/longest_from_start.hpp"
//#include "../../../library/strings/manacher/longest_palindromic_substr.hpp"
#include "../../../library/strings/manacher/count_palindromic_substrs.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int n = 0; n <= 100; n++) {
        for (int tests = 100; tests--;) {
            string s(n, 'a');
            int mx_char = get_rand<int>(0, 5);
            generate(begin(s), end(s), [&]() {return char('a' + get_rand<int>(0, mx_char));});
            vector<int> man = manacher(s);
            vector<vector<bool>> is_pal_naive(n + 1, vector<bool>(n + 1, 1));
            for (int len = 0; len <= n; len++) {
                for (int le = 0; le + len <= n; le++) {
                    int ri = le + len;
                    if(len >= 2)
                        is_pal_naive[le][ri] = (s[le] == s[ri - 1] && is_pal_naive[le + 1][ri - 1]);
                    assert(is_pal(man, le, ri) == is_pal_naive[le][ri]);
                }
            }
            vector<int> longest(longest_from_start(man));
            for (int le = 0; le < n; le++) {
                bool seen_pal = 0;
                for (int ri = n; ri >= le; ri--) {
                    seen_pal |= is_pal_naive[le][ri];
                    assert((le + longest[le] >= ri) == seen_pal);
                }
            }
            vector<vector<int>> count_pals_naive(n + 1, vector<int>(n + 1, 1/*TODO*/));
            pal_count_query pcq(s);
            for (int len = 2/*TODO*/; len <= n; len++) {
                for (int le = 0; le + len <= n; le++) {
                    int ri = le + len;
                    count_pals_naive[le][ri] = count_pals_naive[le+1][ri] + count_pals_naive[le][ri-1] - count_pals_naive[le+1][ri-1];
                    count_pals_naive[le][ri] += is_pal(man, le, ri);
                    assert(pcq.count_pals(le, ri) == count_pals_naive[le][ri]);
                }
            }
            /*
            vector<vector<int>> longest_pal_naive(n + 1, vector<int>(n + 1, 0));
            longest_pal lp(s);
            for (int len = 0; len <= n; len++) {
                for (int le = 0; le + len <= n; le++) {
                    int ri = le + len;
                    if(len)
                        longest_pal_naive[le][ri] = (is_pal_naive[le][ri] ? len : max(longest_pal_naive[le+1][ri], longest_pal_naive[le][ri-1]));
                    assert(lp.get_longest(le, ri) == longest_pal_naive[le][ri]);
                }
            }
            */
        }
    }
    cout << "Hello World\n";
    return 0;
}
