#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int Max = 1e5+3;
int color[Max], Time = 1, timeIn[Max], timeOut[Max], ver[Max], size[Max], cnt[Max];
vector<int> adj[Max];

void dfs(int node, int prev) {
    timeIn[node] = Time;
    ver[Time] = node;
    Time++;
    size[node] = 1;
    for(int to : adj[node]) {
        if(to == prev) continue;
        dfs(to, node);
        size[node] += size[to];
    }
    timeOut[node] = Time;
}

void dfs1(int node, int prev, bool keep = true) {
    int largest = -1, heavyChild = -1;
    for(int to : adj[node]) {
        if(to == prev) continue;
        if(size[to] > largest) {
            largest = size[to];
            heavyChild = to;
        }
    }
    for(int to : adj[node]) {
        if(to == prev || to == heavyChild) continue;
        dfs1(to, node, false);
    }
    if(heavyChild != -1) {
        dfs1(heavyChild, node, true);
    }
    cnt[color[node]]++;
    for(int to : adj[node]) {
        if(to == prev || to == heavyChild) continue;
        for(int i = timeIn[to]; i < timeOut[to]; ++i) {
            cnt[color[ver[i]]]++;
        }
    }
    //process
    
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
    dfs(1, 1);
    dfs1(1, 1);
    return 0;
}







