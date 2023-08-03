#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_B"
//since this causes an O(n) partition check for each call to `lower_bound`,
//causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"

#include "../../../library/strings/suffix_array_related/find_first.hpp"
#include "../../../library/strings/suffix_array_related/find_substr.hpp"
#include "../../../library/strings/suffix_array_related/lcp_interval_tree/find_str.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s, t;
    cin >> s >> t;
    find_first ff(s, 256);
    lcp_tree lt(s, 256);
    {
        auto [le, ri] = find_str(s, ff.sf.sa, string(""));
        assert(le == 0 && ri == ssize(s));
    }
    {
        auto [le, ri] = find_str(lt, string(""));
        assert(le == 0 && ri == ssize(s));
    }
    auto [le, ri] = find_str(s, ff.sf.sa, t);
    auto [le2, ri2] = find_str(lt, t);
    assert(ri - le == ri2 - le2);
    if (ri - le > 0) assert(le == le2);
    vector<int> matches(begin(ff.sf.sa) + le, begin(ff.sf.sa) + ri);
    sort(begin(matches), end(matches));
    {
        int first_match = ff.first_match(t);
        if (matches.empty())
            assert(first_match == -1);
        else {
            assert(first_match == matches[0]);
            assert(t == s.substr(first_match, ssize(t)));
        }
    }
    {
        //test find_substr
        string both = s + '$' + t;
        lcp_query lq_both(both, 256);
        for (int i = 0; i <= ssize(both); i++) {
            auto [le3, ri3] = find_substr(lq_both, i, i);
            assert(le3 == 0 && ri3 == ssize(both));
        }
        auto [le3, ri3] = find_substr(lq_both, ssize(s) + 1, ssize(both));
        assert(ri3 - le3 == 1 + ri - le);
        vector<int> matches_other(begin(lq_both.sf.sa) + le3, begin(lq_both.sf.sa) + ri3);
        matches_other.erase(remove_if(begin(matches_other), end(matches_other), [&](int val) {return val >= ssize(s) + 1;}), end(matches_other));
        sort(begin(matches_other), end(matches_other));
        assert(matches == matches_other);
    }
    for (auto match : matches)
        cout << match << '\n';
    return 0;
}
