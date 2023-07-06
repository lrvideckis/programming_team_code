#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"
//since this causes an O(n) partition check for each call to `lower_bound`,
//causing TLE.
#undef _GLIBCXX_DEBUG
#undef _GLIBCXX_SANITIZE_VECTOR
#undef _GLIBCXX_DEBUG_PEDANTIC
#undef _GLIBCXX_ASSERTIONS
#undef _FORTIFY_SOURCE

#include "../template.hpp"

#include "../../../library/data_structures/wavelet_merge/merge_sort_tree_updates.hpp"
//#define split split_2
//#include "../../../library/data_structures/wavelet_merge/wavelet_tree_updates.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    string s;
    cin >> n >> q >> s;
    merge_sort_tree_updates mstu(vector<int>(n, 0));
    //vector<int> wavelet_init(n);
    //iota(begin(wavelet_init), end(wavelet_init), 0);
    //wavelet_tree_updates wtu(wavelet_init, 0, n);
    for (int i = 0; i < n; i++)
        if (s[i] == '0') {
            mstu.set_active(i, 0);
            //wtu.set_active(i, 0);
        }
    while (q--) {
        int type, k;
        cin >> type >> k;
        if (type == 0) {
            mstu.set_active(k, 1);
            //wtu.set_active(k, 1);
        } else if (type == 1) {
            mstu.set_active(k, 0);
            //wtu.set_active(k, 0);
        } else if (type == 2) {
            int res = mstu.rect_count(k, k + 1, 0, 1);
            //assert(res == wtu.rect_count(k, k + 1, 0, 1));
            cout << res << '\n';
        } else if (type == 3) {
            int num_larger = mstu.rect_count(k, n, 0, 1);
            //assert(num_larger == wtu.rect_count(k, n, 0, 1));
            if (num_larger == 0) cout << -1 << '\n';
            else {
                int res = mstu.kth_smallest(0, 1, mstu.rect_count(0, k, 0, 1) + 1);
                //assert(res == wtu.kth_smallest(k, n, 1));
                cout << res << '\n';
            }
        } else {
            assert(type == 4);
            int num_smaller = mstu.rect_count(0, k + 1, 0, 1);
            //assert(num_smaller == wtu.rect_count(0, k + 1, 0, 1));
            if (num_smaller == 0) cout << -1 << '\n';
            else {
                int res = mstu.kth_smallest(0, 1, num_smaller);
                //assert(res == wtu.kth_smallest(0, k + 1, num_smaller));
                cout << res << '\n';
            }
        }
    }
    return 0;
}
