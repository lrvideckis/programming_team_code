#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/misc/random.hpp"

#include "../../../library/strings/palindrome_query.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int n = 0; n <= 100; n++) {
        for (int tests = 50; tests--;) {
            string s(n, 'a');
            int mx_char = get_rand<int>(0, 5);
            generate(begin(s), end(s), [&]() {return char('a' + get_rand<int>(0, mx_char));});
            sa_query saq(s, 256);
            for (int str_le = 0; str_le <= n; str_le++) {
                for (int str_ri = str_le; str_ri <= n; str_ri++) {
                    auto [le, ri] = saq.find_substr(str_le, str_ri);
                    if (str_le == str_ri)
                        assert(le == 0 && ri == n);
                    if (str_le < n)
                        assert(0 <= le && le <= saq.sa_inv[str_le] && saq.sa_inv[str_le] < ri && ri <= n);
                    for (int i = le; i < ri; i++)
                        assert(s.substr(saq.sa[i], str_ri - str_le) == s.substr(str_le, str_ri - str_le));
                    assert(le == 0 || s.substr(saq.sa[le - 1], str_ri - str_le) != s.substr(str_le, str_ri - str_le));
                    assert(ri == n || s.substr(saq.sa[ri], str_ri - str_le) != s.substr(str_le, str_ri - str_le));
                }
            }
        }
    }
    cout << "Hello World\n";
    return 0;
}
