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
const ll mod = powl(10, 9) + 7;

vector<vector<pair<ll, ll> > > adj;
vector<ll> length;
vector<bool> visited;

void dijkstra(ll node) {
    length[node] = 0;
    priority_queue<pair<ll, ll> > q;//-weight, node
    q.push(mp(0, node));
    while(!q.empty()) {
        node = q.top().second;
        q.pop();
        visited[node] = true;
        for(auto &p : adj[node]) {
            ll to = p.first;
            ll weight = p.second;
            if(!visited[to] && length[to] > weight + length[node]) {
                length[to] = weight + length[node];
                q.push(mp(-length[to], to));
            }
        }
    }
}

int32_t main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    
    return 0;
}















