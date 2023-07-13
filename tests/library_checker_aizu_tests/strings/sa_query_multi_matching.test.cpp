#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_D"
//since this causes an O(n) partition check for each call to `lower_bound`,
//causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"

#include "../../../library/strings/enhanced_suffix_array.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    enhanced_sa esa(s, 128);
    int q;
    cin >> q;
    while (q--) {
        string t;
        cin >> t;
        auto [le, ri] = esa.find(t);
        cout << (!!(ri - le > 0)) << '\n';
    }
    return 0;
}
