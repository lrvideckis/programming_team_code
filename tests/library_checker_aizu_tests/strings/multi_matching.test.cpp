#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_D"
//since this causes an O(n) partition check for each call to `lower_bound`,
//causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"

#include "../../../library/strings/suffix_array_related/find/find_string_bs.hpp"
#include "../../../library/strings/suffix_array_related/find/find_string_bwt.hpp"
#define mn mn_other
#define len len_other
#include "../../../library/strings/suffix_array_related/lcp_interval_tree/find_string_lcpt.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    {
        lcp_tree lt(string(""));
        auto [sa_le, sa_ri, str_le, str_ri] = find_str(string(""), lt.sa, string(""));
        assert(sa_le == 0 && sa_ri == 0 && str_le == 0 && str_ri == 0);
    }
    {
        find_bwt fb(string(""), vector<int>());
        auto [le, ri] = fb.find_str(string(""));
        assert(ssize(le) == 1 && ssize(ri) == 1);
        assert(le[0] == 0 && ri[0] == 0);
    }
    string s;
    cin >> s;
    lcp_tree lt(s);
    find_bwt fb(s, lt.sa);
    {
        auto [sa_le, sa_ri, str_le, str_ri] = find_str(s, lt.sa, string(""));
        assert(sa_le == 0 && sa_ri == ssize(s));
        assert(str_ri - str_le == 0);
    }
    {
        auto [le, ri] = fb.find_str("");
        assert(ssize(le) == 1 && ssize(ri) == 1);
        assert(le[0] == 0 && ri[0] == ssize(s));
    }
    {
        auto [le, ri] = find_str(s, lt, string(""));
        assert(le == 0 && ri == ssize(s));
    }
    int q;
    cin >> q;
    while (q--) {
        string t;
        cin >> t;
        auto [sa_le, sa_ri, str_le, str_ri] = find_str(s, lt.sa, t);
        {
            auto [le, ri] = fb.find_str("a" + t);
            assert(ssize(le) == 2 + ssize(t) && ssize(ri) == 2 + ssize(t) && le.back() == 0 && ri.back() == ssize(s));
            for (int i = ssize(le) - 2; i >= 0; i--)
                assert(ri[i] - le[i] <= ri[i + 1] - le[i + 1]);
            assert(ri[1] - le[1] == sa_ri - sa_le);
            if (sa_le < sa_ri)
                assert(sa_le == le[1] && sa_ri == ri[1]);
        }
        int str_len = str_ri - str_le;
        assert(str_len <= ssize(t));
        assert(s.substr(str_le, str_len) == t.substr(0, str_len));
        assert(str_len == ssize(t) || str_ri == ssize(s) || t[str_len] != s[str_ri]);
        assert((sa_le < sa_ri) == (str_len == ssize(t)));
        auto [le, ri] = find_str(s, lt, t);
        assert(sa_ri - sa_le == ri - le);
        if (sa_ri - sa_le > 0) assert(sa_le == le);
        cout << (!!(sa_ri - sa_le > 0)) << '\n';
    }
    return 0;
}
