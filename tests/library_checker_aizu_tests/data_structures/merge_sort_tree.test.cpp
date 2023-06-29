#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"
//since this causes an O(n) partition check for each call to `equal_range`,
//causing TLE.
#undef _GLIBCXX_DEBUG
#include "../template.hpp"

#include "../../../library/data_structures/uncommon_data_structures/merge_sort_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    merge_sort_tree mst(arr);
    while (q--) {
        int le, ri, x;
        cin >> le >> ri >> x;
        assert(mst.query(le, ri, x, x) == 0);
        cout << mst.query(le, ri, x, x + 1) << '\n';
    }
    return 0;
}
