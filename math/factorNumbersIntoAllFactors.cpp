#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
#define int long long
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define endl '\n'
#define D(x) cout<<#x<<" -> "<<x<<'\n'
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define uni(x) (x).erase(unique(all(x)), (x).end());
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define rep1(i, n) for (int i = 1; i <= (int)(n); ++i)
const ll infll = powl(2, 62)-1;
const ld pi = 4.0*atanl(1.0);
const int mod = powl(10, 9) + 7;

vector<int> getAllFactors(int n) {
    vector<int> factors;
    if(n < 0) n *= -1;
    factors.pb(1);
    int root = sqrtl(n);
    for(int i = 2; i <= root; ++i){
        if(!(n%i)) factors.pb(i);
    }
    int size = factors.size();
    rep(i,size) factors.pb(n/factors[i]);
    return factors;
}

int32_t main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);//freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    vector<int> factors = getAllFactors(n);
    sort(all(factors));
    uni(factors);
    rep(i,factors.size()) cout << factors[i]-1 << ' ';
}







