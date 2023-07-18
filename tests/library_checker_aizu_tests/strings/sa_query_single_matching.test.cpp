#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_B"
//since this causes an O(n) partition check for each call to `lower_bound`,
//causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"

#include "../../../library/strings/suffix_array_related/suffix_array_query.hpp"
#include "../../../library/strings/suffix_array_related/lcp_interval_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s, t;
    cin >> s >> t;
    sa_query saq(s, 256);
    sa_query saq_substr(s + '$' + t, 256);
    lcp_tree lcpt(s, 256);
    {
        auto [le, ri] = saq.find_str("");
        assert(le == 0 && ri == ssize(s));
    }
    for (int i = 0; i <= ssize(s) + 1 + ssize(t); i++) {
        auto [le, ri] = saq.find_substr(i, i);
        assert(le == 0 && ri == ssize(s) + 1 + ssize(t));
    }
    {
        auto [le, ri] = lcpt.find_str("");
        assert(le == 0 && ri == ssize(s));
    }
    auto [le, ri] = saq.find_str(t);
    auto [le2, ri2] = lcpt.find_str(t);
    assert(ri - le == ri2 - le2);
    if (ri - le > 0) assert(le == le2);
    vector<int> matches(begin(saq.sa) + le, begin(saq.sa) + ri);
    sort(begin(matches), end(matches));
    {
        int first_match = saq.find_first(t);
        if (matches.empty())
            assert(first_match == -1);
        else {
            assert(first_match == matches[0]);
            assert(t == s.substr(first_match, ssize(t)));
        }
    }
    for (auto match : matches)
        cout << match << '\n';
    return 0;
}
