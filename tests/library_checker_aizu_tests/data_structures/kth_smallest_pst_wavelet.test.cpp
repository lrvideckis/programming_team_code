#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#include "../template.hpp"

#include "../../../library/data_structures/uncommon_data_structures/kth_smallest.hpp"
#include "../../../library/data_structures/uncommon_data_structures/wavelet_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    vector<int> sorted(arr);
    sort(begin(sorted), end(sorted));
    sorted.erase(unique(begin(sorted), end(sorted)), end(sorted));
    for(int& val : arr)
        val = lower_bound(begin(sorted), end(sorted), val) - begin(sorted) - 50;
    kth_smallest st(arr);
    for (int i = 0; i < n; i++) {
        int mx = arr[i];
        for (int j = i + 1; j <= min(i + 5, n); j++) {
            mx = max(mx, arr[j - 1]);
            assert(st.query(i, j, j - i) == mx);
        }
    }
    wavelet_tree wt(arr, -50, ssize(sorted) - 50);
    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        int res = st.query(l, r, k + 1);
        assert(res == wt.kth_smallest(l, r, k));
        cout << sorted[res + 50] << '\n';
    }
    return 0;
}
