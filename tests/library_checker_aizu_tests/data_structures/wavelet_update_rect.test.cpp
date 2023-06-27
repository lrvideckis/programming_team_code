#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"
//TODO: figure out why debug mode causes TLE
#undef _GLIBCXX_DEBUG
#include "../template.hpp"

#include "../../../library/data_structures/uncommon_data_structures/wavelet_tree_updates.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    vector<int> sorted(arr);
    stable_sort(begin(sorted), end(sorted));
    sorted.erase(unique(begin(sorted), end(sorted)), end(sorted));
    for (int& val : arr)
        val = int(lower_bound(begin(sorted), end(sorted), val) - begin(sorted)) - 30;
    wavelet_tree_updates wtu(arr, -30, ssize(sorted) - 30);
    while (q--) {
        int le, ri, x;
        cin >> le >> ri >> x;
        int start = 0, end = ssize(sorted);
        while (start + 1 < end) {
            int mid = (start + end) / 2;
            if (sorted[mid] <= x) start = mid;
            else end = mid;
        }
        if (sorted[start] != x)
            cout << 0 << '\n';
        else {
            int idx = start - 30;
            assert(wtu.rect_count(le, ri, idx, idx) == 0);
            cout << wtu.rect_count(le, ri, idx, idx + 1) << '\n';
        }
    }
    return 0;
}
