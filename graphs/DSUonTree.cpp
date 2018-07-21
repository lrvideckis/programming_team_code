#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int Max = 1e5+3;
int color[Max], Time = 1, timeIn[Max], timeOut[Max], ver[Max], size[Max], cnt[Max], heavyChild[Max], Depth[Max] = {0}, answer[Max];
vector<int> adj[Max];

void dfs(int node, int prev) {
    timeIn[node] = Time;
    ver[Time] = node;
    Time++;
    size[node] = 1;
    int largest = heavyChild[node] = -1;
    Depth[node] = 1 + Depth[prev];
    for(int to : adj[node]) {
        if(to == prev) continue;
        dfs(to, node);
        size[node] += size[to];
        if(size[to] > largest) {
            largest = size[to];
            heavyChild[node] = to;
        }
    }
    timeOut[node] = Time;
}

void dfs1(int node, int prev, bool keep = true) {
    for(int to : adj[node]) {
        if(to == prev || to == heavyChild[node]) continue;
        dfs1(to, node, false);
    }
    if(heavyChild[node] != -1) {
        dfs1(heavyChild[node], node, true);
    }
    cnt[color[node]]++;
    for(int to : adj[node]) {
        if(to == prev || to == heavyChild[node]) continue;
        for(int i = timeIn[to]; i < timeOut[to]; ++i) {
            cnt[color[ver[i]]]++;
        }
    }
    if(!keep) {
        for(int i = timeIn[node]; i < timeOut[node]; ++i) {
            cnt[color[ver[i]]]--;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    dfs(1, 1);
    dfs1(1, 1);
    for(int i = 1; i <= n; ++i) {
        cout << answer[i] << ' ';
    }
    cout << '\n';
    return 0;
}





