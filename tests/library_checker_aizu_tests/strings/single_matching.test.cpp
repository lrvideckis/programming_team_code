#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_B"
//since this causes an O(n) partition check for each call to `lower_bound`,
//causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"
#include "../../../library/contest/random.hpp"

#include "../../../library/strings/suffix_array_related/find/find_str.hpp"
#include "../../../library/strings/suffix_array_related/find/find_substrs_concatenated.hpp"
#include "../../../library/strings/suffix_array_related/lcp_interval_tree/find_str.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s, t;
    cin >> s >> t;
    lcp_tree lt(s, 256);
    {
        auto [le, ri] = find_str(lt, string(""));
        assert(le == 0 && ri == ssize(s));
    }
    auto [le, ri] = find_str(s, lt.sf.sa, t);
    auto [le2, ri2] = find_str(lt, t);
    assert(ri - le == ri2 - le2);
    if (ri - le > 0) assert(le == le2);
    vector<int> matches(begin(lt.sf.sa) + le, begin(lt.sf.sa) + ri);
    sort(begin(matches), end(matches));
    {
        //test find_substrs_concated
        string both = s + '$' + t;
        int t_start = ssize(s) + 1;
        lcp_query lq_both(both, 256);
        vector<int> splits = {0, ssize(t)};
        for (int num_splits = get_rand(0, 4); num_splits--;)
            splits.push_back(get_rand(0, ssize(t)));
        sort(begin(splits), end(splits));
        vector<pair<int, int>> subs;
        for (int i = 1; i < ssize(splits); i++)
            subs.emplace_back(splits[i - 1] + t_start, splits[i] + t_start);
        assert(!subs.empty());
        auto [le3, ri3] = find_substrs_concated(lq_both, subs);
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
