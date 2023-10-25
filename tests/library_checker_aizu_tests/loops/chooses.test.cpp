#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_11_D"
#include "../template.hpp"

#include "../../../library/loops/chooses.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k;
    cin >> n >> k;
    auto f = [&](int mask) {
        cout << mask << ':';
        for (int bit = 0; bit < n; bit++) {
            if ((mask >> bit) & 1)
                cout << ' ' << bit;
        }
        cout << '\n';
    };
    chooses(n, k, f);
    return 0;
}
