#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../template.hpp"

#include "../../../library/data_structures/wavelet_merge/bool_bit.hpp"

const int MAX_BIT = 51;

vector<bool_bit> init_prebools(const vector<long long>& arr) {
    const int N = ssize(arr);
    vector<bool_bit> prebools;
    for (int bit = 0; bit < MAX_BIT; bit++) {
        vector<bool> curr(N);
        for (int i = 0; i < N; i++)
            curr[i] = (arr[i] >> bit) & 1;
        prebools.emplace_back(curr);
    }
    return prebools;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int n = 0; n <= 500; n++) {
        bool_bit bb(vector<bool>(n));
        for (int i = 0; i <= n; i++)
            assert(bb.popcount(i) == 0);
    }
    int n, q;
    cin >> n >> q;
    vector<long long> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    vector<bool_bit> prebools = init_prebools(arr);
    assert(ssize(prebools) == MAX_BIT);
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int i;
            int delta;
            cin >> i >> delta;
            arr[i] += delta;
            for (int bit = 0; bit < MAX_BIT; bit++)
                prebools[bit].set(i, (arr[i] >> bit) & 1);
        } else {
            assert(type == 1);
            int le, ri;
            cin >> le >> ri;
            long long sum = 0;
            for (int bit = 0; bit < MAX_BIT; bit++) {
                if (ri - le == 1)
                    sum += (1LL << bit) * prebools[bit].on(le);
                else
                    sum += (1LL << bit) * prebools[bit].popcount(le, ri);
            }
            cout << sum << '\n';
        }
    }
}
