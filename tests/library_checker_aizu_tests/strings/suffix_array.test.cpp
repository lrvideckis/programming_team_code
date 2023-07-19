#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "../template.hpp"

#include "../../../library/strings/suffix_array_related/find_str.hpp"
#include "../../../library/strings/suffix_array_related/find_substr.hpp"

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
    auto [sa, sa_inv] = get_sa(s, 256);
    vector<int> lcp = get_lcp_array({sa, sa_inv}, s);
    {
        auto [le, ri] = find_str(s, sa, string(""));
        assert(le == 0 && ri == n);
        assert(ssize(sa) == n);
        assert(ssize(sa_inv) == n);
        assert(ssize(lcp) == n - 1);
    }
    for (int i : {0, ssize(s), ssize(s) / 2}) {
        auto [le, ri] = find_substr({sa, sa_inv}, lcp, i, i);
        assert(le == 0 && ri == n);
    }
    for (int i = 0; i < n; i++) {
        assert(sa[sa_inv[i]] == i);
        assert(sa_inv[sa[i]] == i);
    }
    for (auto val : sa)
        cout << val << " ";
    cout << '\n';
}
