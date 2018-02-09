#include <bits/stdc++.h>
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
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
#define rep(i, n) for (int32_t i = 0; i < (int32_t)(n); ++i)
#define rep1(i, n) for (int32_t i = 1; i <= (int32_t)(n); ++i)
const ld pi = 4.0*atanl(1.0);
const ll infll = (ll)(1e18) + 10;
const ll mod = powl(10, 9) + 7;

vector<vector<int> > adj, memo;
vector<int> depth, parent;
vector<bool> visited;

void dfs(int node, int Depth = 0) {
    depth[node] = Depth;
    visited[node] = true;
    for(int x : adj[node]) {
        if(!visited[x]) {
            parent[x] = node;
            dfs(x, Depth+1);
        }
    }
}

int LCA(int x, int y) {
    if(depth[x] < depth[y]) swap(x,y);
    int diff = depth[x] - depth[y];
    for(int k = 17; k >= 0; --k) {
        if(diff&(1<<k)) {
            x = memo[x][k];
        }
    }
    for(int k = 17; k >= 0; --k) {
        if(memo[x][k] != memo[y][k]) {
            x = memo[x][k];
            y = memo[y][k];
        }
    }
    if(x != y) x = parent[x];
    return x;
}

int main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n;
    cin >> n;
    adj.resize(n+1);
    depth.resize(n+1);
    parent.resize(n+1);
    visited.resize(n+1,false);
    int a,b;
    rep(i,n-1) {
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    parent[1] = 0;
    dfs(1);
    memo.resize(n+1, vector<int>(18,0));
    rep1(i,n) memo[i][0] = parent[i];
    rep1(k,17) rep1(i,n) memo[i][k] = memo[memo[i][k-1]][k-1];
    
    return 0;
}
















