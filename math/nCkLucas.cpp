#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;

ll power(ll a, ll b, ll c) {
    if (b <= 0) return 1;
    ll temp = power(a, b / 2, c) % c;
    if (b % 2 == 0) {
        return (temp * temp) % c;
    }
    return (((a * temp) % c) * temp) % c;
}

//lucas theorem to calculate n choose k in O(log(k))
//***use prime moduli***
//***can only use with: prime moduli < 1e6***
struct NchooseKLucas {
    int range, mod;
    vector<ll> fact,ifact;
    NchooseKLucas(int currMod) {
        this->mod = currMod;
        range = currMod-1;
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
    //classic n choose k
    ll choose(int n, int k) {
        if(k < 0 || k > n || n < 0) return 0;
        return ((1LL*fact[n]*ifact[k])%this->mod * 1LL*ifact[n-k])%this->mod;
    }
    //n choose k, using the lucas theorem
    ll chooseLucas(ll n, ll k) {
        if(k < 0 || k > n || n < 0) return 0;
        if(k == 0) {
            return 1;
        }

        int ni = n % this->mod;
        int ki = k % this->mod;

        return (this->chooseLucas(n/this->mod, k/this->mod) * this->choose(ni,ki)) % this->mod;
    }
    //bars and stars problem: given n objects, each with an endless supply this returns
    //the number of ways to choose k of them.
    ll multiChoose(ll n, ll k) {
        return chooseLucas(n+k-1, n-1);
    }

};

ll modInverse(ll a, ll b){
    return 1<a ? b - modInverse(b%a,a)*b/a : 1;
}

const int mod1 = 29, mod2 = 34483;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    if(k > n*m) {
        cout << "0\n";
        return 0;
    }
    NchooseKLucas nk1(mod1), nk2(mod2);
    int sum1 = 0, sum2 = 0;
    for(int i = 0;; ++i) {
        int remaining = k-(m+1)*i;
        if(remaining < 0) break;

        if(i%2 == 0) {

            sum1 += (nk1.chooseLucas(n, i)*nk1.multiChoose(n, remaining))%mod1;

            sum2 += (nk2.chooseLucas(n, i)*nk2.multiChoose(n, remaining))%mod2;

        } else {

            sum1 -= (nk1.chooseLucas(n, i)*nk1.multiChoose(n, remaining))%mod1;

            sum2 -= (nk2.chooseLucas(n, i)*nk2.multiChoose(n, remaining))%mod2;

        }

        sum1 = (sum1%mod1+mod1)%mod1;
        sum2 = (sum2%mod2+mod2)%mod2;
    }

    int actualMod = mod1*mod2;

    int res = (sum1*mod2%actualMod*modInverse(mod2, mod1))%actualMod + (sum2*mod1%actualMod*modInverse(mod1, mod2))%actualMod;

    res %= actualMod;
    res += actualMod;
    res %= actualMod;

    cout << res << '\n';

    return 0;
}
