#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<vector<pair<ll, ll> > > adj;
vector<ll> length;

void dijkstra(int node) {
    length[node] = 0;
    set<pair<ll, int> > q;//weight, node
    q.insert({0, node});
    while(!q.empty()) {
        auto it = q.begin();
        node = it->second;
        q.erase(it);
        for(auto &p : adj[node]) {
            int to = p.first;
            ll weight = p.second;
            if(length[to] > weight + length[node]) {
                q.erase({length[to], to});
                length[to] = weight + length[node];
                q.insert({length[to], to});
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















