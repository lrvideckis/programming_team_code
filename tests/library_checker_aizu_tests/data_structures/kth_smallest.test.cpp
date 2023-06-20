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
        val = lower_bound(begin(sorted), end(sorted), val) - begin(sorted);
    kth_smallest st(arr);
    wavelet_tree wt(arr);
    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        int res = st.query(l, r, k);
        assert(res == wt.kth(l, r, k));
        cout << sorted[res] << '\n';
    }
    return 0;
}
