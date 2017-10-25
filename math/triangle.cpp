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
const int mod = powl(10, 9) + 1;

bool tri(int x) {
    if(x <= 0) return false;
    int temp = (int)((sqrtl(8*x+1)-1)/2.0);
    return (temp*(temp+1)/2 == x);
}

int32_t main() {//ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    //freopen("e.in", "r", stdin);
    //freopen("e.out", "w", stdout);
    for(int i = -5; i < 25; ++i) 
        cout << i << ' ' << tri(i) << '\n';
    return 0;
}


























