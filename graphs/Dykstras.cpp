#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<vector<pair<ll, ll> > > adj;
vector<ll> length;
vector<bool> visited;

void dijkstra(int node) {
    length[node] = 0;
    priority_queue<pair<ll, int> > q;//-weight, node
    q.push({0, node});
    while(!q.empty()) {
        node = q.top().second;
        q.pop();
        visited[node] = true;
        for(auto &p : adj[node]) {
            int to = p.first;
            ll weight = p.second;
            if(!visited[to] && length[to] > weight + length[node]) {
                length[to] = weight + length[node];
                q.push({-length[to], to});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    return 0;
}















