#define _USE_MATH_DEFINES//M_PI
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
typedef long long ll;
typedef long double ld;

ll choose(int n, int k) {
    if(k < 0 || k > n || n < 0) return 0;
    if(k == 0 || k == n) {
        return 1;
    }
    static map<pair<int, int> , ll> table;
    if(table.count({n,k})) return table[{n,k}];
    return table[{n,k}] = choose(n-1, k-1)+choose(n-1, k);
}

int main() {
    cout << "n,k,choose(n,k):\n";
    for(int n = -1; n < 5; n++) {
        for(int k = -1; k < 5; ++k) {
            cout << n << '\t' << k << '\t' << choose(n, k) << '\n';
        }
    }
    return 0;
}

