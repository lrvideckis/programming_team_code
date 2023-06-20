#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"
//since this causes an O(n) partition check for each call to `equal_range`,
//causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"

#include "../../../library/data_structures/uncommon_data_structures/merge_sort_tree.hpp"
#include "../../../library/data_structures/uncommon_data_structures/wavelet_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    merge_sort_tree mst(arr);
    vector<int> sorted(arr);
    sort(begin(sorted), end(sorted));
    sorted.erase(unique(begin(sorted), end(sorted)), end(sorted));
    for(int& val : arr)
        val = int(lower_bound(begin(sorted), end(sorted), val) - begin(sorted)) - 30;
    wavelet_tree wt(arr, -30, ssize(sorted)-30);
    while (q--) {
        int le, ri, x;
        cin >> le >> ri >> x;
        int res = mst.query(le, ri, x);
        auto it = lower_bound(begin(sorted), end(sorted), x);
        if(it == end(sorted) || (*it) != x) {
            assert(res == 0);
        } else {
            int idx = int(it - begin(sorted)) - 30;
            assert(wt.count(le,ri,idx, idx+1) == res);
            assert(wt.count(le,ri,idx, idx) == 0);
        }
        cout << res << '\n';
    }
    return 0;
}
