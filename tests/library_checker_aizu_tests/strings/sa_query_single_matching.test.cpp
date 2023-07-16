#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_B"
//since this causes an O(n) partition check for each call to `lower_bound`,
//causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"

#include "../../../library/strings/suffix_array.hpp"
#include "../../../library/strings/suffix_array_query.hpp"
//#include "../../../library/strings/enhanced_suffix_array.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s, t;
    cin >> s >> t;
    auto [sa, rank, lcp] = get_suffix_array(s, 128);
    sa_query sq(s, sa, rank, lcp);
    //enhanced_sa esa(s, 128);
    auto [le, ri] = sq.find(t);
    //auto [le2, ri2] = esa.find(t);
    //assert(ri - le == ri2 - le2);
    //if (ri - le > 0) assert(le == le2);
    vector<int> matches(begin(sa) + le, begin(sa) + ri);
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
    for (auto match : matches)
        cout << match << '\n';
    return 0;
}
