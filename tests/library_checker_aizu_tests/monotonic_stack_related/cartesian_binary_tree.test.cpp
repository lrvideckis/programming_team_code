#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"
#include "../template.hpp"

#include "../../../library/monotonic_stack/cartesian_binary_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    auto mr = mono_st(a, less()), p = cart_binary_tree(mr);
    for (int i = 0; i < n; i++)
        cout << (p[i] == n ? i : p[i]) << " ";
    return 0;
}
