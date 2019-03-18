#include <bits/stdc++.h>
using namespace std;
//#define ll long long
typedef long long ll;

const ll Max = 1e6+10;
ll fact[Max], ifact[Max];
ll memo[Max][2];//memo[i][T/F] = ways to fill first i balls with last ball == Blue

//returns a^pw % mod
ll power(ll a, ll pw, ll mod) {
    ll res = 1;
    while(pw) {
        if(pw & 1) res = (res*a)%mod;
        a = (a*a)%mod;
        pw >>= 1;
    }
    return res;
}



struct NchooseK {
    int range, mod;
    vector<int> fact,ifact;
    NchooseK(int currMod) {
        this->mod = currMod;
        range = (int)1e6+3;
        //range = currMod-1;//TODO: uncomment this to use chooseLucas
        fact.resize(range+1);
        ifact.resize(range+1);
        calcFacts();
    }
    void calcFacts() {
        fact[0] = 1;
        for(int i = 1; i <= range; ++i) {
            fact[i] = (1LL*fact[i-1]*i)%this->mod;
        }
        ifact[range] = power(fact[range], this->mod-2, this->mod);
        for(int i = range-1; i >= 0; --i) {
            ifact[i] = (1LL*ifact[i+1]*(i+1))%this->mod;
        }
    }
    int modFact(int n, int &e) {
        if(n <= 1) return 1;
        ll res = modFact(n/this->mod, e);
        e += n/this->mod;
        if ((n/this->mod)%2 == 1) return 1LL*res*(fact[n%this->mod]*(this->mod-1)%this->mod)%this->mod;
        return 1LL*res*fact[n%this->mod]%this->mod;
    }
    int calcChoose(int n, int k) {
        int e1 = 0, e2 = 0, e3 = 0;
        int a1 = modFact(n, e1);
        int a2 = modFact(k, e2);
        int a3 = modFact(n-k, e3);
        if (e1-e2-e3 > 0) return 0;
        return (1LL*a1*power(1LL*a2*a3%this->mod, this->mod-2, this->mod)%this->mod);
    }
    ll choose(int n, int k) {
        if(k < 0 || k > n || n < 0) return 0;
        return ((1LL*fact[n]*ifact[k])%this->mod * 1LL*ifact[n-k])%this->mod;
    }
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t;
    cin >> t;
    NchooseK nk(2);
    while(t--) {
        ll n, m;
        cin >> n >> m;
        nk.mod = m;
        nk.calcFacts();
        for(ll i = 1; i <= n; ++i) {
            memo[i][0] = memo[i][1] = 0;
        }
        memo[1][0] = 1;
        memo[1][1] = 1;
        for(ll i = 2; i <= n; ++i) {
            memo[i][1] = memo[i-1][0];
            memo[i][1] %= m;
            memo[i][0] = memo[i-1][0];
            memo[i][0] += memo[i-1][1];
            memo[i][0] %= m;
        }
        ll res = 0;
        if(n%2 == 0) {
            res += nk.calcChoose(n, n/2);
            res %= m;
            res -= n/2 + 1;
            res %= m;
            res += m;
            res %= m;
        }
        res += memo[n][0];
        res += memo[n][1];
        res %= m;
        res += m;
        res %= m;
        cout << res << '\n';
    }
    return 0;
}



