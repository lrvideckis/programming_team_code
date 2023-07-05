#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"
#include "../template.hpp"

#include "../../../library/data_structures/wavelet_merge/bool_presum.hpp"

vector<bool_presum> init_presums(const vector<int>& arr) {
    const int N = ssize(arr);
    vector<bool_presum> presums;
    for (int bit = 0; bit < 30; bit++) {
        vector<bool> the_bools(N);
        for (int i = 0; i < N; i++)
            the_bools[i] = (arr[i] >> bit) & 1;
        presums.emplace_back(the_bools);
    }
    return presums;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int sz = 0; sz < 1111; sz++) {
        vector<bool> bools(sz, 0);
        bools.back() = 1;
        bool_presums tmp(bools);
        assert(tmp.mask.back());
    }
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    vector<bool_presum> presums = init_presums(arr);
    assert(ssize(presums) == 30);
    while (q--) {
        int le, ri;
        cin >> le >> ri;
        long long sum = 0;
        for (int bit = 0; bit < 30; bit++)
            if (ri - le == 1)
                sum += (1LL << bit) * presums[bit].on(le);
            else
                sum += (1LL << bit) * (presums[bit].popcount(ri) - presums[bit].popcount(le));
        cout << sum << '\n';
    }
}
