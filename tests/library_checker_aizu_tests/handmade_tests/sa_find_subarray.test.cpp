#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/misc/random.hpp"

#include "../../../library/strings/suffix_array_related/suffix_array_query.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for(int n = 0; n <= 100; n++) {
        for (int tests = 10; tests--;) {
            string s(n, 'a');
            int mx_char = get_rand<int>(0,5);
            generate(begin(s), end(s), [&]() {return char('a' + get_rand<int>(0,mx_char));});
            cerr << "s: " << s << endl;
            sa_query saq(s, 256);
            for(int le = 0; le <= n; le++) {
                for(int ri = le + 1/*TODO: test empty subarray too*/; ri <= n; ri++) {
                    auto [sa_le, sa_ri] = saq.find_substr(le, ri);
                    assert(0 <= sa_le && sa_le <= saq.sa_inv[le] && saq.sa_inv[le] < sa_ri && sa_ri <= n);
                    for(int i = sa_le; i < sa_ri; i++) {
                        assert(s.substr(saq.sa[i], ri - le) == s.substr(le, ri - le));
                    }
                    //TODO: assert indexes le-1, ri are not equal
                }
            }
        }
    }
    cout << "Hello World\n";
    return 0;
}
