#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
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

int n,m;
vector<vector<int> > adj, adjInv;
vector<int> scc;
int sccID;
vector<bool> visited;

void dfs1(int curr, stack<int> &seen) {
    visited[curr] = true;
    for(int x : adj[curr]) {
        if(!visited[x]) {
            dfs1(x, seen);
        }
    }
    seen.push(curr);
}

void dfs2(int curr) {
    visited[curr] = true;
    scc[curr] = sccID;
    for(int x : adjInv[curr]) {
        if(!visited[x]) {
            dfs2(x);
        }
    }
}

void calcSCC() {
    visited.resize(n+1,false);
    stack<int> seen;
    rep1(i,n) {
        if(!visited[i]) {
            dfs1(i, seen);
        }
    }
    visited.clear();
    visited.resize(n+1,false);
    sccID = 0;
    while(!seen.empty()) {
        while(!seen.empty() && visited[seen.top()]) seen.pop();
        if(!seen.empty()) {
            dfs2(seen.top());
            sccID++;
        }
    }
}

int main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin >> n >> m;
    scc.resize(n+1);
    adj.resize(n+1);
    adjInv.resize(n+1);
    int a,b;
    vector<pair<int, int> > edges;
    rep(i,m) {
        cin >> a >> b;
        adj[a].pb(b);
        adjInv[b].pb(a);
        edges.pb(mp(a,b));
    }
    calcSCC();
    //now sccID = number of SCC's
    rep1(i,n) cout << i << ' ' << scc[i] << '\n';
    return 0;
}














