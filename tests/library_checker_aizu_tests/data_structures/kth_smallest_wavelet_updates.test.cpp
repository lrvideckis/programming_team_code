#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#include "../template.hpp"

#include "../../../library/data_structures/wavelet_merge/wavelet_tree_updates.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    vector<int> sorted(arr);
    sort(begin(sorted), end(sorted));
    sorted.erase(unique(begin(sorted), end(sorted)), end(sorted));
    for (int& val : arr) {
        int start = 0, end = int(ssize(sorted));
        while (start + 1 < end) {
            int mid = (start + end) / 2;
            if (sorted[mid] <= val) start = mid;
            else end = mid;
        }
        assert(sorted[start] == val);
        val = start - 50;
    }
    wavelet_tree_updates wtu(arr, -50, int(ssize(sorted)) - 50, vector<bool>(n, 1));
    for (int i = 0; i < n; i++) {
        int mx = arr[i];
        for (int j = i + 1; j <= min(i + 5, n); j++) {
            mx = max(mx, arr[j - 1]);
            assert(wtu.kth_smallest(i, j, j - i) == mx);
        }
    }
    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << sorted[wtu.kth_smallest(l, r, k + 1) + 50] << '\n';
    }
    return 0;
}
