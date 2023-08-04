#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "../template.hpp"

#include "../../../library/strings/suffix_array_related/find_str.hpp"
#include "../../../library/strings/suffix_array_related/find_substrs_concatenated.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    {
        string s;
        auto [sa, sa_inv] = get_sa(s, 256);
        assert(get_lcp_array({sa, sa_inv}, s).empty());
    }
    {
        string s = "a";
        auto [sa, sa_inv] = get_sa(s, 256);
        assert(get_lcp_array({sa, sa_inv}, s).empty());
    }
    {
        vector<int> arr;
        auto [sa, sa_inv] = get_sa(arr, 100'005);
        vector<int> lcp = get_lcp_array({sa, sa_inv}, arr);
        assert(sa.empty() && sa_inv.empty() && lcp.empty());
    }
    string s;
    cin >> s;
    int n = ssize(s);
    lcp_query lq(s, 256);
    {
        auto [le, ri] = find_str(s, lq.sf.sa, string(""));
        assert(le == 0 && ri == n);
        assert(ssize(lq.sf.sa) == n);
        assert(ssize(lq.sf.sa_inv) == n);
        assert(ssize(lq.lcp) == n - 1);
    }
    {
        auto [le, ri] = find_substrs_concated(s, lq, {{0, 0}});
        assert(le == 0 && ri == n);
    }
    {
        auto [le, ri] = find_substrs_concated(s, lq, {{0, 0}, {n, n}});
        assert(le == 0 && ri == n);
    }
    {
        auto [le, ri] = find_substrs_concated(s, lq, {{0, 0}, {n / 2, n / 2}, {n, n}});
        assert(le == 0 && ri == n);
    }
    for (int i = 0; i < n; i++) {
        assert(lq.sf.sa[lq.sf.sa_inv[i]] == i);
        assert(lq.sf.sa_inv[lq.sf.sa[i]] == i);
    }
    for (auto val : lq.sf.sa)
        cout << val << " ";
    cout << '\n';
}
