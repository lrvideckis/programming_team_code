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

struct fenwickTree {
    vector<int> bit;
    int n;
    void init(int n) {
        this->n = n;
        bit.assign(n,0);
    }
    int sum(int r) {
        int ret = 0;
        for(; r >= 0; r = (r&(r+1))-1)
            ret += bit[r];
        return ret;
    }
    void add(int idx, int d) {
        for(; idx < n; idx = idx | (idx+1)) 
            bit[idx] += d;
    }
    int sum(int l, int r) {
        return sum(r) - sum(l-1);
    }
    void init(vector<int> a) {
        init(a.size());
        for(size_t i = 0; i < a.size(); ++i)
            add(i,a[i]);
    }
};

int32_t main() {//ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    //freopen("e.in", "r", stdin);
    //freopen("e.out", "w", stdout);
    
    return 0;
}


























