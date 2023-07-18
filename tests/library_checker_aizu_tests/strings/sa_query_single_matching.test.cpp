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
    sa_query sq(s, 256);
    string both = s + '$' + t;
    sa_query saq_substr(both, 256);
    lcp_tree lcpt(s, 256);
    {
        auto [le, ri] = sq.find_str("");
        assert(le == 0 && ri == ssize(s));
    }
    for (int i = 0; i <= ssize(both); i++) {
        auto [le, ri] = saq_substr.find_substr(i, i);
        assert(le == 0 && ri == ssize(both));
    }
    {
        auto [le, ri] = lcpt.find_str("");
        assert(le == 0 && ri == ssize(s));
    }
    auto [le, ri] = sq.find_str(t);
    auto [le2, ri2] = lcpt.find_str(t);
    assert(ri - le == ri2 - le2);
    if (ri - le > 0) assert(le == le2);
    vector<int> matches(begin(sq.sa) + le, begin(sq.sa) + ri);
    sort(begin(matches), end(matches));
    {
        int first_match = sq.find_first(t);
        if (matches.empty())
            assert(first_match == -1);
        else {
            assert(first_match == matches[0]);
            assert(t == s.substr(first_match, ssize(t)));
        }
    }
    auto [le3, ri3] = saq_substr.find_substr(ssize(s) + 1, ssize(both));
    assert(ri3 - le3 == 1 + ri - le);
    vector<int> matches_other(begin(saq_substr.sa) + le3, begin(saq_substr.sa) + ri3);
    matches_other.erase(remove_if(begin(matches_other), end(matches_other), [&](int val) {return val >= ssize(s) + 1;}), end(matches_other));
    sort(begin(matches_other), end(matches_other));
    assert(matches == matches_other);
    for (auto match : matches)
        cout << match << '\n';
    return 0;
}
