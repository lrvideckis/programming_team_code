#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = pow(10, 9)+7;

ll power(ll a, ll b) {
    if (b <= 0) return 1;
    ll temp = power(a, b / 2) % mod;
    if (b % 2 == 0) {
        return (temp * temp) % mod;
    }
    else {
        return (((a * temp) % mod) * temp) % mod;
    }
}

struct NchooseK {
    int range;
    vector<int> fact,ifact;
    NchooseK() {
        range = (int)1e6;
        fact.resize(range+1);
        ifact.resize(range+1);
        calcFacts();
    }
    void calcFacts() {
        fact[0] = 1;
        for(ll i = 1; i <= range; ++i) {
            fact[i] = (1LL*fact[i-1]*i)%mod;
        }
        ifact[range] = power(fact[range], mod-2);
        for(int i = range-1; i >= 0; --i) {
            ifact[i] = (1LL*ifact[i+1]*(i+1))%mod;
        }
    }
    int choose(int n, int k) {
        if(k < 0 || k > n || n < 0) return 0;
        return ((1LL*fact[n]*ifact[k])%mod * 1LL*ifact[n-k])%mod;
    }
};

int main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    NchooseK nk;
    cout << nk.choose(4,2) << '\n';
    cout << nk.choose(10,5) << '\n';
    return 0;
}
