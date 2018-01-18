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

//given an array of n elements, generate all 2^n subsets of those elements.
//time complexity: O(n*2^n)
//space complexity: O(n)

int32_t main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n;  
    cin >> n;
    vector<int> arr(n);
    rep(i,n) cin >> arr[i];
    for(int i = 0; i < (1<<n); ++i) {
        vector<int> subset;
        rep(j,n)if(i&(1<<j)) subset.pb(arr[j]);
        //process subset
        rep(j,subset.size()) cout << subset[j] << ' ';cout << endl;
    }
    return 0;
}



















