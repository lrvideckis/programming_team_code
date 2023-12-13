#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../template.hpp"

#include "../../../library/data_structures/seg_tree_uncommon/iterative.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    {
        //test empty seg tree
        seg_tree st_empty{vector<int>()};
        iter_seg_tree ist(st_empty);
        ist.update_iter(0, 0, 1);
        long long res = ist.query_iter(0, 0);
        assert(res == 0);
        ist.st.update(0, 0, 1);
        res = ist.st.query(0, 0);
        assert(res == 0);
    }
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    seg_tree st_curr(arr);
    iter_seg_tree ist(st_curr);
    assert(n <= ist.st.pw2 && ist.st.pw2 < 2 * n);
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int idx;
            long long x;
            cin >> idx >> x;
            if (q % 2)
                ist.update_iter(idx, idx + 1, x);
            else
                ist.st.update(idx, idx + 1, x);
            ist.update_iter(idx, idx, 1);
            ist.st.update(idx, idx, 1);
        } else {
            assert(type == 1);
            int l, r;
            cin >> l >> r;
            if (q % 2)
                cout << ist.query_iter(l, r) << '\n';
            else
                cout << ist.st.query(l, r) << '\n';
            {
                long long res = ist.query_iter(l, l);
                assert(res == 0);
            }
            {
                long long res = ist.query_iter(r, r);
                assert(res == 0);
            }
            {
                long long res = ist.st.query(l, l);
                assert(res == 0);
            }
            {
                long long res = ist.st.query(r, r);
                assert(res == 0);
            }
        }
    }
    return 0;
}
