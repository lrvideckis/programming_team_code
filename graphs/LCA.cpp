#include <bits/stdc++.h>
using namespace std;

const int Max = 1e5+3, Log = 20+1;
vector<int> adj[Max];
int memo[Max][Log];
int depth[Max];

void dfs(int node, int prev, int Depth = 0) {
    depth[node] = Depth;
    memo[node][0] = prev;
    for(int i = 1; i < Log; ++i) {
        memo[node][i] = memo[memo[node][i-1]][i-1];
    }
    for(int to : adj[node]) {
        if(to == prev) continue;
        dfs(to, node, Depth+1);
    }
}

int LCA(int x, int y) {
    if(depth[x] < depth[y]) swap(x,y);
    int diff = depth[x] - depth[y];
    for(int k = Log-1; k >= 0; --k) {
        if(diff&(1<<k)) {
            x = memo[x][k];
        }
    }
    for(int k = Log-1; k >= 0; --k) {
        if(memo[x][k] != memo[y][k]) {
            x = memo[x][k];
            y = memo[y][k];
        }
    }
    if(x != y) x = memo[x][0];
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    int a,b;
    for(int i = 0; i < n-1; ++i) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,1);
    return 0;
}
















