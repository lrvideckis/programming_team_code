#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct NchooseK {
    ll mod;
    ll range;
    vector<ll> fact,ifact;
    NchooseK() {
        (this->mod) = (ll)1e9+7;
        this->range = 1000000;
        fact.resize(this->range);
        ifact.resize(this->range);
        calcFacts();
    }
    ll power(ll a, ll b) {
        if (b <= 0) return 1;
        ll temp = power(a, b / 2) % this->mod;
        if (b % 2 == 0) {
            return (temp * temp) % this->mod;
        }
        else {
            return (((a * temp) % this->mod) * temp) % this->mod;
        }
    }
    void calcFacts() {
        fact[0] = 1;
        for(ll i = 1; i < this->range; ++i) {
            fact[i] = (fact[i-1]*i)%(this->mod);
        }
	    ifact[this->range-1] = power(fact[this->range-1], this->mod-2);
	    for(int i = this->range-2; i >= 0; --i) {
	        ifact[i] = (ifact[i+1] * (i+1)) % this->mod;
        }
    }
    ll gcd(ll a, ll b, ll &x, ll &y) { 
        if (a == 0) {
            x = 0;
            y = 1;
            return b;
        }
        ll x1, y1;
        ll d = gcd(b % a, a, x1, y1);
        x = y1 - (b / a) * x1;
        y = x1;
        return d;
    }
    ll divide(ll a, ll b) {
        ll m = (this->mod);
        ll x, y;
        ll g = gcd(b, m, x, y);
        if (g != 1) {
            cerr << "Bad gcd!" << endl;
            for(;;);
        }
        x = (x % m + m) % m;
        return ((ll)a*(ll)x)%m;
    }
    ll choose(ll n, ll k) {
        if(k < 0 || k > n || n < 0) return 0;
        return ((fact[n]*ifact[k])%this->mod * ifact[n-k])%this->mod;
    }
};

int main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    NchooseK nk;
    cout << nk.choose(4,2) << '\n';
    cout << nk.choose(10,5) << '\n';
    return 0;
}
