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
        auto [sa_le, sa_ri] = fb.find_str("");
        assert(sa_le == 0 && sa_ri == ssize(s));
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
            auto [sa_le2, sa_ri2] = fb.find_str(t);
            assert(sa_ri2 - sa_le2 == sa_ri - sa_le);
            if (sa_le < sa_ri)
                assert(sa_le == sa_le2 && sa_ri == sa_ri2);
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
