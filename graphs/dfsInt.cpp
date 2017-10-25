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
//const int mod = pow(10, 9) + 7;

vector<vector<int> > adj;
vector<bool> visited;
vector<int> previous;

void initialize(int n) {
    adj.resize(n+1);
    visited.resize(n+1, false);
    previous.resize(n+1);
    return;
}

void dfs(int start) {
    visited[start] = true;
    for(int x : adj[start]) {
        if(!visited[x]) {
            dfs(x);
            previous[x] = start;
        }
    }
}

int32_t main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n;
    cin >> n;
    initialize(n);
    return 0;
}
