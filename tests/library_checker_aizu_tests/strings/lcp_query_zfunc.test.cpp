#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"

#include "../../../library/strings/suffix_array_related/suf_cmp.hpp"
#include "../../../library/strings/suffix_array_related/lcp_query.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    lcp_query lq(s, 256);
    //test `less` function
    {
        for (int num_tests = 50; num_tests--;) {
            auto le = get_rand<int>(0, ssize(s) - 1);
            auto ri = get_rand<int>(0, ssize(s) - 1);
            if (le > ri)
                swap(le, ri);
            assert(suf_cmp(lq.sf.sa_inv, le, ri) == (s.substr(le) < s.substr(ri)));
        }
    }
    for (int i = 0; i < ssize(s); i++)
        cout << lq.get_lcp(i, 0) << " ";
    cout << '\n';
    return 0;
}
