#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"

#include "../../../library/data_structures/binary_indexed_tree/rupq.hpp"
#include "../../../library/data_structures/binary_indexed_tree/rurq.hpp"
#include "../../../library/data_structures/binary_indexed_tree/lower_bound.hpp"
#include "../../../library/data_structures/lazy_segment_tree/lower_bound.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q;
    cin >> n >> q;
    vector<long long> arr(n);
    vector<int> arr_int(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr_int[i] = int(arr[i]);
    }
    BIT<long long> bit(arr);
    seg_tree st(arr_int);
    bit_rurq<long long> bit_rr(arr);
    vector<long long> suf_sum(n);
    partial_sum(rbegin(arr), rend(arr), rbegin(suf_sum));
    bit_rupq<long long> bit_i(suf_sum);
    for (int i = 0; i < n; i++) {
        assert(arr[i] == bit.sum(i, i + 1));
        assert(bit_i.get_index(i) == bit.sum(i, n));
        assert(bit_i.get_index(i) == suf_sum[i]);
    }
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int p, x;
            cin >> p >> x;
            bit.update(p, x);
            st.update(p, p + 1, x);
            bit_rr.update(p, p + 1, x);
            bit_i.update(0, p + 1, x);
        } else {
            int l, r;
            cin >> l >> r;
            long long res = bit.sum(l, r);
            {
                long long bit_i_result = bit_i.get_index(l);
                if (r < n) bit_i_result -= bit_i.get_index(r);
                assert(res == bit_i_result);
            }
            assert(res == bit_rr.sum(l, r));
            cout << res << '\n';
        }
        auto sum = get_rand<long long>(0LL, (long long)(1e12));
        int pos_bit = lower_bound(bit, sum);
        int pos_st = lower_bound(st, sum);
        assert(pos_bit == pos_st);
    }
    return 0;
}
