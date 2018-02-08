#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<vector<int> > tree, memo;
vector<int> parent, depth;
vector<bool> visited;
int upperBound, maxDepth;

void dfs(int node) {
    visited[node] = true;
    for(int x : tree[node]) {
        if(!visited[x]) {
            depth[x] = depth[node] + 1;
            maxDepth = max(maxDepth, depth[x]);
            parent[x] = node;
            dfs(x);
        }
    }
}

int pathLength(int i, int j) {
    if(depth[i] < depth[j]) swap(i,j);
    int distance = depth[i] - depth[j];
    for(int bit = upperBound; bit >= 0; --bit) {
        if(distance&(1<<bit)) {
            i = memo[i][bit];
        }
    }
    for(int bit = upperBound; bit >= 1; --bit) {
        if(memo[i][bit] == memo[j][bit] && memo[i][bit-1] != memo[j][bit-1]) {
            distance += 1<<bit;
            i = memo[i][bit-1];
            j = memo[j][bit-1];
        }
    }
    if(i != j) distance += 2;
    return distance;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    tree.resize(n+1);
    parent.resize(n+1);
    visited.resize(n+1);
    depth.resize(n+1);
    int a,b;
    for(int i = 0; i < n-1; ++i) {
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    maxDepth = depth[1] = parent[1] = 0;
    dfs(1);
    upperBound = (int)floor(log2(maxDepth))+1;
    memo.resize(n+1,vector<int>(upperBound+1));
    for(int i = 1; i <= n; ++i) {
        memo[i][0] = parent[i];
    }
    for(int k = 1; k <= upperBound; ++k) {
        for(int i = 1; i <= n; ++i) {
            memo[i][k] = memo[memo[i][k-1]][k-1];
        }
    }
    //usage: pathLength(i,j);
    return 0;
}











