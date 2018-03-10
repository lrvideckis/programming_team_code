#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;//order_of_key, find_by_order
template<class TI>
using indexed_set = tree<TI,null_type,less<TI>,rb_tree_tag,tree_order_statistics_node_update>;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define mp make_pair
#define D(x) cout<<#x<<" -> "<<x<<'\n'
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define uni(x) (x).erase(unique(all(x)), (x).end())
#define rep(i, n) for (int32_t i = 0; i < (int32_t)(n); ++i)
#define rep1(i, n) for (int32_t i = 1; i <= (int32_t)(n); ++i)
const ld pi = 4.0*atanl(1.0);
const int mod = 1e9+7;


int main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    //freopen("e.in", "r", stdin);
    //freopen("e.out", "w", stdout);
    int n;
    cin >> n;
    vector<ll> arr(n);
    for(ll &x : arr) cin >> x;
    return 0;
}







































