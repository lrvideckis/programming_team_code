#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_D"
#include "../template.hpp"
#include "../../../library/strings/suffix_array_related/find/find_string_bwt.hpp"
#define mn mn_other
#define max_val max_val_other
#include "../../../library/strings/suffix_array_related/lcp_interval_tree/find_string_lcpt.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
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
        auto [lcpt_le, lcpt_ri] = find_str(s, lt, t);
        {
            auto [bwt_le, bwt_ri] = fb.find_str("a" + t);
            assert(ssize(bwt_le) == 2 + ssize(t) && ssize(bwt_ri) == 2 + ssize(t) && bwt_le.back() == 0 && bwt_ri.back() == ssize(s));
            for (auto i = ssize(bwt_le) - 2; i >= 0; i--)
                assert(bwt_ri[i] - bwt_le[i] <= bwt_ri[i + 1] - bwt_le[i + 1]);
            assert(bwt_ri[1] - bwt_le[1] == lcpt_ri - lcpt_le);
            if (lcpt_le < lcpt_ri)
                assert(lcpt_le == bwt_le[1]);
        }
        cout << (!!(lcpt_ri - lcpt_le > 0)) << '\n';
    }
    return 0;
}
