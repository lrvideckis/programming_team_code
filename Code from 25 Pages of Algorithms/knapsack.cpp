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

int table[2001][2001];
int weight[2001], value[2001];//one based indexing for weight and value arrays for easy implementation

int knapsack(int c, int n) {
    for(int i = 0; i <= n; ++i) {
        for(int w = 0; w <= c; ++w) {
            if(!i||!w) table[i][w] = 0;
            else if(weight[i] <= w)
                table[i][w] = max(value[i] + table[i-1][w-weight[i]], table[i-1][w]);
            else table[i][w] = table[i-1][w];
        }
    }
    return table[n][c];
}

int32_t main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    double c;
    int n;
    while(cin>>c>>n) {
        rep1(i,n) cin >> value[i] >> weight[i];
        knapsack((int)c, n);
        vector<int> packed;
        int item = n, cap = c;
        while(item > 0) {
            if(table[item][cap] - table[item-1][cap-weight[item]] == value[item]) {
                packed.pb(item);
                cap -= weight[item];
            }
            --item;
        }
        cout<<packed.size()<<'\n';
        rep(i,packed.size())cout<<packed[i]-1<<' ';cout<<'\n';
    }
    return 0;
}













