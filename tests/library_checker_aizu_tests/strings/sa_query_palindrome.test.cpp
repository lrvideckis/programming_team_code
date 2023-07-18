#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"
#include "../template.hpp"

#include "../../../library/strings/suffix_array_related/suffix_array_query/get_lcp.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    int n = ssize(s);
    s = s + '$' + string(rbegin(s), rend(s));
    sa_query sq(s, 256);
    for (int i = 0; i < n; i++) {
        for (int j = i; j < min(i + 2, n); j++)
            cout << get_lcp(sq, j, (n - i - 1) + n + 1) * 2 - (i == j) << " ";
    }
    cout << '\n';
    return 0;
}
