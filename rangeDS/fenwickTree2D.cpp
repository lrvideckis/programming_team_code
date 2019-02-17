#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct fenwickTree2D {
    vector<vector<ll>> bit;
    int n, m;
    fenwickTree2D(int _n, int _m) {
        n = _n;
        m = _m;
        bit.resize(n+1, vector<ll>(m+1,0));
    }
    ll sum(int i, int j) {
        ll ret = 0;
        for(; i >= 0; i = (i&(i+1))-1)
            for(int jj = j; jj >= 0; jj = (jj&(jj+1))-1)
                ret += bit[i][jj];
        return ret;
    }
    void add(int i, int j, ll d) {
        for(; i <= n; i = i | (i+1))
            for(int jj = j; jj <= m; jj = jj | (jj+1))
                bit[i][jj] += d;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    const int n = 100;
    const int m = 300;
    const int maxVal = 1000000;
    fenwickTree2D ft(n,m);
    vector<vector<ll>> naive(n, vector<ll>(m));
    srand(time(NULL));
    for(int k = 0; k < 1000; ++k) {
        const int i = rand()%n;
        const int j = rand()%m;
        if(rand()%2) {
            const int val = rand()%maxVal;
            ft.add(i,j,val);
            naive[i][j] += val;
        } else {
            ll naiveSum = 0;
            for(int ii = 0; ii <= i; ++ii) {
                for(int jj = 0; jj <= j; ++jj) {
                    naiveSum += naive[ii][jj];
                }
            }
            ll fastSum = ft.sum(i,j);
            if(naiveSum == fastSum) {
                //cout << "correct\n";
            } else {
                cout << "incorrect: " << naiveSum << ' ' << fastSum << '\n';
            }
        }
    }
    return 0;
}

















