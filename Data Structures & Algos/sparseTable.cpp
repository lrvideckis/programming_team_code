#include <bits/stdc++.h>
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;//__builtin_popcount(n)
using namespace __gnu_pbds;//order_of_key, key_of_order
template<class TI>
using indexed_set = tree<TI,null_type,less<TI>,rb_tree_tag,tree_order_statistics_node_update>;
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define D(x) cout<<#x<<" -> "<<x<<'\n'
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define uni(x) (x).erase(unique(all(x)), (x).end())
#define rep(i, n) for (ll i = 0; i < (ll)(n); ++i)
#define rep1(i, n) for (ll i = 1; i <= (ll)(n); ++i)
const ld pi = 4.0*atanl(1.0);
const ll infll = (ll)(1e18) + 10;
const ll mod = powl(10, 9) + 7;

struct sparseTable {
    vector<vector<ll> > memo;
    int maxPow;
    sparseTable(vector<ll> &arr) {
        int n = arr.size();
        maxPow = floor(log2(n))+1;
        memo.resize(n, vector<ll>(maxPow));
        rep(j,maxPow) {
            rep(i,n) {
                if(i+(1<<j)-1<n) {
                    memo[i][j] = (j?min(memo[i][j-1], memo[i+(1<<(j-1))][j-1]):arr[i]);
                } else break;
            }
        }
    }
    ll query(int l, int r) {
        int j = floor(log2(r-l+1));
        return min(memo[l][j], memo[r-(1<<j)+1][j]);
    }
};

int main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n;
    cin >> n;
    vector<ll> arr(n);
    for(ll &x : arr) cin >> x;
    cout << "arr:\n";
    for(ll &x : arr) cout << x << ' ';cout << '\n';
    sparseTable st(arr);
    rep(i,n) {
        for(int j = i; j < n; ++j) {
            cout << "query: [i,j]: " << st.query(i,j) << '\n';
        }
    }
    return 0;
}











































