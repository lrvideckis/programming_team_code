/*

FIND A BETTER VERSION OF THIS

*/


#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
typedef complex<double> cd;

const int mod = 998244353;

ll power(ll a, ll b, ll c) {
    if (b <= 0) return 1;
    ll temp = power(a, b / 2, c) % c;
    if (b % 2 == 0) {
        return (temp * temp) % c;
    }
    return (((a * temp) % c) * temp) % c;
}

void ntt(vector<ll> &v, bool rev=false) {
    int n = v.size(), i, j, m;
    for(i = 0, j = 1; j < n-1; ++j) {
        for(int k = n >> 1; k > (i ^= k); k >>= 1);
        if(i > j) {
            swap(v[i], v[j]);
        }
    }
    for(int m = 2; m <= n; m *= 2) {
        ll wn = power(5, (mod-1)/m, mod);
        if(rev) {
            wn = power(wn, mod-2, mod);
        }
        for(i = 0; i < n; i += m) {
            ll w = 1;
            for(int j1 = i, j2 = i+m/2; j2 < i+m; ++j1, ++j2) {
                ll t1 = v[j1], t2 = w*v[j2]%mod;
                v[j1] = t1+t2;
                v[j2] = t1+mod-t2;
                while(v[j1] >= mod) v[j1]-=mod;
                while(v[j2] >= mod) v[j2]-=mod;
                w = w*wn%mod;
            }
        }
    }
    if(rev) {
        ll rv = power(n, mod-2, mod);
        for(i = 0; i < n; ++i) {
            v[i]=v[i]*rv%mod;
        }
    }
}

vector<ll> mult(vector<ll> P,vector<ll> Q,bool resize) {
    if(resize) {
        int maxind = 0, pi = 0, qi = 0, i;
        int s=2;
        for(i = 0; i < P.size(); ++i) {
            if(P[i]) {
                pi = i;
            }
        }
        for(i = 0; i < Q.size(); ++i) {
            if(Q[i]) {
                qi = i;
            }
        }
        maxind = pi+qi+1;
        while(s*2 < maxind) s *= 2;
        P.resize(s*2);
        Q.resize(s*2);
    }
    ntt(P);
    ntt(Q);
    for(int i = 0; i < P.size(); ++i) {
        P[i] = P[i]*Q[i]%mod;
    }
    ntt(P,true);
    while(P.size() && P.back() == 0) P.pop_back();
    return P;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<int> a = {1,2,3};
    vector<int> b = {4,5,6};
    vector<int> prod = mult(a, b, true);
    for(int i = 0; i < prod.size(); ++i) {
        cout << prod[i] << ' ';
    }
    cout << '\n';
    return 0;
}











































