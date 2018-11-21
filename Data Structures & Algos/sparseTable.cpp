#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct sparseTable {
    vector<vector<ll> > memo;
    vector<int> logTwo;
    int maxPow;
    sparseTable(vector<ll> &arr) {
        int n = arr.size();
        logTwo.resize(n+1,0);
        for(int i = 2; i <= n; ++i) logTwo[i] = 1 + logTwo[i/2];
        maxPow = logTwo[n]+1;
        memo.resize(n, vector<ll>(maxPow));
        for(int j = 0; j < maxPow; ++j) {
            for(int i = 0; i < n; ++i) {
                if(i+(1<<j)-1<n) {
                    memo[i][j] = (j?min(memo[i][j-1], memo[i+(1<<(j-1))][j-1]):arr[i]);
                } else break;
            }
        }
    }
    ll query(int l, int r) {
        int j = logTwo[r-l+1];
        return min(memo[l][j], memo[r-(1<<j)+1][j]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<ll> arr(n);
    for(ll &x : arr) cin >> x;
    cout << "arr:\n";
    for(ll &x : arr) cout << x << ' ';cout << '\n';
    sparseTable st(arr);
    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            cout << i << ' ' << j << ' ';
            cout << "query: [i,j]: " << st.query(i,j) << '\n';
        }
    }
    return 0;
}











































