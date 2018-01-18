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


int GetCeilIndex(vector<int> &arr, vector<int> &T, int l, int r, int key) {
    while (r - l > 1) {
        int m = (l+r)>>1;
        if (arr[T[m]] >= key) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}
 
vector<int> longestIncreasingSubsequence(vector<int> &arr) {
    int n = arr.size();
    vector<int> tailIndices(n, 0);
    vector<int> prevIndices(n, -1);
    int len = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[tailIndices[0]]) {
            tailIndices[0] = i;
        } else if (arr[i] > arr[tailIndices[len-1]]) {
            prevIndices[i] = tailIndices[len-1];
            tailIndices[len++] = i;
        } else {
            int pos = GetCeilIndex(arr, tailIndices, -1, len-1, arr[i]);
            prevIndices[i] = tailIndices[pos-1];
            tailIndices[pos] = i;
        }
    }
    vector<int> index;
    for (int i = tailIndices[len-1]; len--; i = prevIndices[i]) index.pb(i);
    reverse(all(index));
    return index;
}

int32_t main() {//ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n;
    while(cin>>n) {
        vector<int> arr(n);
        rep(i,n)cin>>arr[i];
        vector<int> temp = longestIncreasingSubsequence(arr);
        cout<<temp.size()<<'\n';
        rep(i,temp.size())cout<<temp[i]<<' ';
        cout<<'\n';
    }
    return 0;
}




















