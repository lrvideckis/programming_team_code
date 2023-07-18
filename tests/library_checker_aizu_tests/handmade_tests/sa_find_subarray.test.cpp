#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/misc/random.hpp"

#include "../../../library/strings/suffix_array_related/suffix_array_query.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int n = 0; n <= 40; n++) {
        for (int tests = 30; tests--;) {
            string s(n, 'a');
            int mx_char = get_rand<int>(0, 5);
            generate(begin(s), end(s), [&]() {return char('a' + get_rand<int>(0, mx_char));});
            sa_query sq(s, 256);
            for (int str_le = 0; str_le <= n; str_le++) {
                for (int str_ri = str_le; str_ri <= n; str_ri++) {
                    auto [le, ri] = sq.find_substr(str_le, str_ri);
                    if (str_le == str_ri)
                        assert(le == 0 && ri == n);
                    if (str_le < n)
                        assert(0 <= le && le <= sq.sa_inv[str_le] && sq.sa_inv[str_le] < ri && ri <= n);
                    for (int i = le; i < ri; i++)
                        assert(s.substr(sq.sa[i], str_ri - str_le) == s.substr(str_le, str_ri - str_le));
                    assert(le == 0 || s.substr(sq.sa[le - 1], str_ri - str_le) != s.substr(str_le, str_ri - str_le));
                    assert(ri == n || s.substr(sq.sa[ri], str_ri - str_le) != s.substr(str_le, str_ri - str_le));
                }
            }
        }
    }
    cout << "Hello World\n";
    return 0;
}
