#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_D"
//since this causes an O(n) partition check for each call to `lower_bound`,
//causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"

#include "../../../library/strings/suffix_array_related/suffix_array_query.hpp"
#include "../../../library/strings/suffix_array_related/lcp_interval_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    sa_query saq(s, 256);
    lcp_tree lcpt(s, 256);
    {
        auto [le, ri] = saq.find("");
        assert(le == 0 && ri == ssize(s));
    }
    {
        auto [le, ri] = lcpt.find("");
        assert(le == 0 && ri == ssize(s));
    }
    int q;
    cin >> q;
    while (q--) {
        string t;
        cin >> t;
        auto [le, ri] = saq.find(t);
        auto [le2, ri2] = lcpt.find(t);
        assert(ri - le == ri2 - le2);
        if (ri - le > 0) assert(le == le2);
        cout << (!!(ri - le > 0)) << '\n';
    }
    return 0;
}
