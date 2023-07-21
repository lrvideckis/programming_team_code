#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "../template.hpp"

#include "../../../library/strings/suffix_array_related/lcp_interval_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    int n = ssize(s);
    lcp_tree lcpt(s, 256);
    {
        auto [le, ri] = lcpt.find_str("");
        assert(le == 0 && ri == n);
        assert(ssize(lcpt.sf.sa) == n);
        assert(ssize(lcpt.sf.sa_inv) == n);
        assert(ssize(lcpt.lcp) == n - 1);
    }
    for (auto val : lcpt.sf.sa)
        cout << val << " ";
    cout << '\n';
}
