#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_quotients"
#include "../template.hpp"

#include "../../../library/loops/quotients.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    long long n;
    cin >> n;
    vector<long long> quots;
    {
        long long prev_ri = 0;
        auto f = [&](long long le, long long ri) -> void {
            assert(n / le == n / ri);
            assert(le == 1 || n / le < n / (le - 1));
            assert(n / (ri + 1) < n / ri);
            assert(prev_ri + 1 == le);
            prev_ri = ri;
            quots.push_back(n / le);
        };
        quotients(n, f);
        assert(prev_ri == n);
    }
    cout << ssize(quots) << '\n';
    for(int i = ssize(quots) - 1; i >= 0; i--) {
        cout << quots[i] << ' ';
    }
    cout << '\n';
    return 0;
}
