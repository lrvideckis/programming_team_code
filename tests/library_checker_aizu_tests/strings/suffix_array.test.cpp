#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "../template.hpp"

#include "../../../library/strings/suffix_array.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    assert(get_suffix_array<string>("", 128).lcp.empty());
    assert(get_suffix_array<string>("a", 128).lcp.empty());
    string s;
    cin >> s;
    int n = ssize(s);
    auto [sa, rank, _] = get_suffix_array(s, 128);
    assert(ssize(sa) == n);
    assert(ssize(rank) == n);
    for (int i = 0; i < n; i++) {
        assert(sa[rank[i]] == i);
        assert(rank[sa[i]] == i);
    }
    for (auto val : sa)
        cout << val << " ";
    cout << '\n';
}
