#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_D"
//since this causes an O(n) partition check for each call to `lower_bound`,
//causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"

#include "../../../library/strings/suffix_array.hpp"
#include "../../../library/strings/suffix_array_query.hpp"
#include "../../../library/strings/enhanced_suffix_array.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    auto [sa, rank, lcp] = get_suffix_array(s, 128);
    sa_query sq(s, sa, rank, lcp);
    enhanced_sa esa(s, sa, rank, lcp);
    {
        auto [le, ri] = sq.find("");
        assert(le == 0 && ri == ssize(s));
    }
    {
        auto [le, ri] = esa.find("");
        assert(le == 0 && ri == ssize(s));
    }
    int q;
    cin >> q;
    while (q--) {
        string t;
        cin >> t;
        auto [le, ri] = sq.find(t);
        auto [le2, ri2] = esa.find(t);
        assert(ri - le == ri2 - le2);
        if (ri - le > 0) assert(le == le2);
        cout << (!!(ri - le > 0)) << '\n';
    }
    return 0;
}
