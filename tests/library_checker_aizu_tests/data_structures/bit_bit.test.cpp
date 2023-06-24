#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../template.hpp"

#include "../../../library/data_structures/uncommon_data_structures/wavelet_tree_updates.hpp"

const int MAX_BIT = 51;

vector<bit_bit> init_prebits(const vector<long long>& arr) {
    const int N = ssize(arr);
    vector<bit_bit> prebits;
    for (int bit = 0; bit < MAX_BIT; bit++) {
        prebits.emplace_back(N);
        for (int i = 0; i < N; i++)
            prebits[bit].set(i, (arr[i] >> bit) & 1);
    }
    return prebits;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    {
        bit_bit bb(0);
        assert(bb.popcount(0, 0) == 0);
    }
    int n, q;
    cin >> n >> q;
    vector<long long> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    vector<bit_bit> prebits = init_prebits(arr);
    assert(ssize(prebits) == MAX_BIT);
    while (q--) {
        int type;
        cin >> type;
        if(type == 0) {
            int i;
            int delta;
            cin >> i >> delta;
            arr[i] += delta;
            for(int bit = 0; bit < MAX_BIT; bit++)
                prebits[bit].set(i, (arr[i] >> bit) & 1);
        } else {
            assert(type == 1);
            int le, ri;
            cin >> le >> ri;
            long long sum = 0;
            for (int bit = 0; bit < MAX_BIT; bit++)
                sum += (1LL << bit) * prebits[bit].popcount(le, ri);
            cout << sum << '\n';
        }
    }
}
