#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"
#include "../template.hpp"

#include "../../../library/data_structures/wavelet_merge/merge_sort_tree_updates.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    string s;
    cin >> n >> q >> s;
    merge_sort_tree_updates mstu(vector<int>(n, 0));
    for(int i = 0; i < n; i++)
        if(s[i] == '0')
            mstu.set_active(i, 0);
    while(q--) {
        int type, k;
        cin >> type >> k;
        if(type == 0) {
            mstu.set_active(k, 1);
        } else if(type == 1) {
            mstu.set_active(k, 0);
        } else if(type == 2) {
            cout << mstu.rect_count(k, k + 1, 0, 1) << '\n';
        } else if(type == 3) {
            int num_larger = mstu.rect_count(k + 1, n, 0, 1);
            if (num_smaller == 0) cout << -1 << '\n';
            else {
                cout << mstu.kth_smallest(0, 1, mstu.rect_count(0, k + 1, 0, 1) + 1) << '\n';
            }
        } else {
            assert(type == 4);
            int num_smaller = mstu.rect_count(0, k, 0, 1);
            if (num_smaller == 0) cout << -1 << '\n';
            else cout << mstu.kth_smallest(0, 1, num_smaller) << '\n';
        }
    }
    return 0;
}
