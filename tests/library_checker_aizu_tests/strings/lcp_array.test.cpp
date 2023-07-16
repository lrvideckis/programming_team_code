#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"
#include "../template.hpp"

#include "../../../library/strings/suffix_array.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    int n = ssize(s);
    auto [sa, rank, lcp] = get_suffix_array(s, 128);
    assert(ssize(lcp) == n - 1);
    cout << 1LL * n * (n + 1) / 2 - accumulate(begin(lcp), end(lcp), 0LL) << '\n';
}
