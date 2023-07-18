#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "../template.hpp"

#include "../../../library/strings/suffix_array_related/suffix_array_query.hpp"
#include "../../../library/strings/suffix_array_related/lcp_interval_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    {
        string s;
        auto [sa, sa_inv] = get_sa(s, 256);
        assert(get_lcp_array(s, sa, sa_inv).empty());
        s = "a";
        tie(sa, sa_inv) = get_sa(s, 256);
        assert(get_lcp_array(s, sa, sa_inv).empty());
    }
    string s;
    cin >> s;
    int n = ssize(s);
    sa_query saq(s, 256);
    lcp_tree lcpt(s, 256);
    assert(saq.sa == lcpt.sa);
    assert(saq.sa_inv == lcpt.sa_inv);
    assert(saq.lcp == lcpt.lcp);
    {
        auto [le, ri] = saq.find_str("");
        assert(le == 0 && ri == n);
        assert(ssize(saq.sa) == n);
        assert(ssize(saq.sa_inv) == n);
        assert(ssize(saq.lcp) == n - 1);
    }
    for (int i : {0, ssize(s), ssize(s) / 2}) {
        auto [le, ri] = saq.find_substr(i, i);
        assert(le == 0 && ri == n);
    }
    {
        auto [le, ri] = lcpt.find_str("");
        assert(le == 0 && ri == n);
        assert(ssize(lcpt.sa) == n);
        assert(ssize(lcpt.sa_inv) == n);
        assert(ssize(lcpt.lcp) == n - 1);
    }
    for (int i = 0; i < n; i++) {
        assert(saq.sa[saq.sa_inv[i]] == i);
        assert(saq.sa_inv[saq.sa[i]] == i);
    }
    for (auto val : saq.sa)
        cout << val << " ";
    cout << '\n';
}
