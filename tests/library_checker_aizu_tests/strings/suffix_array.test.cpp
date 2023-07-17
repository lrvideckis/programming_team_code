#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "../template.hpp"

#include "../../../library/strings/suffix_array_related/suffix_array.hpp"
#include "../../../library/strings/suffix_array_related/enhanced_suffix_array.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    {
        vector<int> lcp = get_suffix_array<string>("", 256).lcp;
        assert(lcp.empty());
        lcp = get_suffix_array<string>("a", 256).lcp;
        assert(lcp.empty());
    }
    string s;
    cin >> s;
    int n = ssize(s);
    auto [sa, rank, lcp] = get_suffix_array(s, 256);
    enhanced_sa esa(s, sa, rank, lcp);
    auto [le, ri] = esa.find("");
    assert(le == 0 && ri == n);
    assert(ssize(sa) == n);
    assert(ssize(rank) == n);
    assert(ssize(lcp) == n - 1);
    for (int i = 0; i < n; i++) {
        assert(sa[rank[i]] == i);
        assert(rank[sa[i]] == i);
    }
    for (auto val : sa)
        cout << val << " ";
    cout << '\n';
}
