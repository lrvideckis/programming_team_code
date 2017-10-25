#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct NchooseK {
    ll mod;
    ll range;
    vector<ll> fact;
    NchooseK() {
        (this->mod) = (ll)1e9+7;
        this->range = 1000000;
        fact.resize(this->range);
        calcFacts();
    }
    void calcFacts() {
	    fact[0] = 1;
        for(ll i = 1; i < this->range; ++i) {
		    fact[i] = (fact[i-1]*i)%(this->mod);
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
        if(k < 0 || k > n) return 0;
	    return divide(fact[n], (fact[k] * fact[n-k])%(this->mod));
    }

};

int main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    NchooseK nk;
    cout << nk.choose(10,5) << '\n';
    return 0;
}
