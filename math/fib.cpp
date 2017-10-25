#define _USE_MATH_DEFINES//M_PI
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
#define int long long
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define uni(x) (x).erase(unique(all(x)), (x).end());
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define rep1(i, n) for (int i = 1; i <= (int)(n); ++i)
const ll infll = powl(2, 62)-1;
const int mod = pow(10, 9) + 7;

//**O(log(n))**
unordered_map<ll,ll> table;
int fib(int n) {
    if(n<2) return 1;
    if(table.find(n) != table.end()) return table[n];
    table[n] = (fib((n+1) / 2)*fib(n/2) + fib((n-1) / 2)*fib((n-2) / 2)) % mod;
    return table[n];
}

int32_t main() {
    rep(i, 10) cout << i << ' ' << fib(i) << endl;
    return 0;
}




















