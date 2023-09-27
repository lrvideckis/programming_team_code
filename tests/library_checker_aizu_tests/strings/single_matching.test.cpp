#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_B"
//since this causes an O(n) partition check for each call to `lower_bound`,
//causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"
#include "../../../library/contest/random.hpp"

#include "../../../library/strings/suffix_array_related/find/find_string_bs.hpp"
#include "../../../library/strings/suffix_array_related/find/find_string_bwt.hpp"
#include "../../../library/strings/suffix_array_related/find/find_substrings_concatenated.hpp"
#define mn mn_other
#define len len_other
#include "../../../library/strings/suffix_array_related/lcp_interval_tree/find_string_lcpt.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s, t;
    cin >> s >> t;
    lcp_tree lt(s);
    {
        auto [le, ri] = find_str(s, lt, string(""));
        assert(le == 0 && ri == ssize(s));
    }
    auto [sa_le, sa_ri, str_le, str_ri] = find_str(s, lt.sa, t);
    int str_len = str_ri - str_le;
    assert(s.substr(str_le, str_len) == t.substr(0, str_len));
    assert(str_len <= ssize(t));
    assert(str_len == ssize(t) || str_ri == ssize(s) || t[str_len] != s[str_ri]);
    assert((sa_le < sa_ri) == (str_len == ssize(t)));
    auto [le, ri] = find_str(s, lt, t);
    assert(sa_ri - sa_le == ri - le);
    if (sa_ri - sa_le > 0) assert(sa_le == le);
    vector<int> matches(begin(lt.sa) + sa_le, begin(lt.sa) + sa_ri);
    sort(begin(matches), end(matches));
    {
        //test find via BWT
        find_bwt fb(s, lt.sa);
        auto ret = fb.find_str(t);
        assert(sa_ri - sa_le == ret[0][1] - ret[0][0]);
        if (sa_le < sa_ri) assert(ret[0][0] == sa_le);
    }
    {
        //test find_substrs_concated
        string both = s + '$' + t;
        int t_start = ssize(s) + 1;
        lcp_query lq_both(both, 256);
        vector<int> splits = {0, ssize(t)};
        for (int num_splits = get_rand(0, 4); num_splits--;)
            splits.push_back(get_rand(0, ssize(t)));
        sort(begin(splits), end(splits));
        vector<array<int, 2>> subs;
        for (int i = 1; i < ssize(splits); i++)
            subs.push_back({splits[i - 1] + t_start, splits[i] + t_start});
        assert(!subs.empty());
        auto [sa_le2, sa_ri2, str_le2, str_ri2] = find_substrs_concated(lq_both, subs);
        assert(both.substr(str_le2, str_ri2 - str_le2) == t);
        assert(sa_ri2 - sa_le2 == 1 + sa_ri - sa_le);
        vector<int> matches_other(begin(lq_both.sa) + sa_le2, begin(lq_both.sa) + sa_ri2);
        matches_other.erase(remove_if(begin(matches_other), end(matches_other), [&](int val) {return val >= ssize(s) + 1;}), end(matches_other));
        sort(begin(matches_other), end(matches_other));
        assert(matches == matches_other);
    }
    for (auto match : matches)
        cout << match << '\n';
    return 0;
}
