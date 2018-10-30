#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll power(ll a, ll b, ll c) {
    if (b <= 0) return 1;
    ll temp = power(a, b / 2, c) % c;
    if (b % 2 == 0) {
        return (temp * temp) % c;
    }
    return (((a * temp) % c) * temp) % c;
}

struct NchooseK {
    int range, mod;
    vector<ll> fact,ifact;
    NchooseK(int currMod) {
        this->mod = currMod;
        range = (int)1e6+3;
        fact.resize(range+1);
        ifact.resize(range+1);
        calcFacts();
    }
    void calcFacts() {
        fact[0] = 1;
        for(ll i = 1; i <= range; ++i) {
            fact[i] = (1LL*fact[i-1]*i)%this->mod;
        }
        ifact[range] = power(fact[range], this->mod-2, this->mod);
        for(int i = range-1; i >= 0; --i) {
            ifact[i] = (1LL*ifact[i+1]*(i+1))%this->mod;
        }
    }
    ll modFact(ll n, ll &e) {
        if(n <= 1) return 1;
        ll res = modFact(n/this->mod, e);
        e += n/this->mod;
        if ((n/this->mod)%2 == 1) return res*(fact[n%this->mod]*(this->mod-1)%this->mod)%this->mod;
        return res*fact[n%this->mod]%this->mod;
    }
    ll calcChoose(ll n, ll k) {
        ll e1 = 0, e2 = 0, e3 = 0;
        ll a1 = modFact(n, e1);
        ll a2 = modFact(k, e2);
        ll a3 = modFact(n-k, e3);
        if (e1-e2-e3 > 0) return 0;
        return (a1*power(a2*a3%this->mod, this->mod-2, this->mod)%this->mod);
    }
    ll choose(int n, int k) {
        if(k < 0 || k > n || n < 0) return 0;
        return ((1LL*fact[n]*ifact[k])%this->mod * 1LL*ifact[n-k])%this->mod;
    }
};

int main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    NchooseK nk(1000000009);
    cout << nk.choose(4,2) << '\n';
    cout << nk.choose(10,5) << '\n';
    return 0;
}
