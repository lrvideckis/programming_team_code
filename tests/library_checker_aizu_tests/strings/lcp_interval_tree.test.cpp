#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "../template.hpp"

#include "../../../library/strings/suffix_array_related/lcp_interval_tree/find_string.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    int n = ssize(s);
    lcp_tree lt(s, 256);
    {
        auto [le, ri] = find_str(lt, string(""));
        assert(le == 0 && ri == n);
        assert(ssize(lt.sa) == n);
        assert(ssize(lt.sa_inv) == n);
        assert(ssize(lt.lcp) == n - 1);
    }
    for (auto val : lt.sa)
        cout << val << " ";
    cout << '\n';
}
