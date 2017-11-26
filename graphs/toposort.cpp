#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
#define int long long
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define D(x) cout<<#x<<" -> "<<x<<'\n'
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define uni(x) (x).erase(unique(all(x)), (x).end());
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define rep1(i, n) for (int i = 1; i <= (int)(n); ++i)
const ll infll = powl(2, 62)-1;
const ld pi = 4.0*atanl(1.0);
const int mod = powl(10, 9) + 7;

int32_t main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n, m, t;//vertices, edges, total time(weight)
    cin >> n >> m >> t;
    vector<vector<pair<int, int> > > adj(n+1);
    vector<int> indegree(n+1,0);
    int x,y,w;
    rep(i,m) {
        cin >> x >> y >> w;
        adj[x].pb(mp(y,w));
        indegree[y]++;
    }
    queue<int> zeroin;
    rep1(i,n) if(indegree[i] == 0) zeroin.push(i);
    vector<int> topo(n);
    int pos = 0;
    while(!zeroin.empty()) {
        int curr = zeroin.front();
        zeroin.pop();
        topo[pos++] = curr;
        for(pair<int,int> to : adj[curr]) {
            indegree[to.first]--;
            if(indegree[to.first] == 0) {
                zeroin.push(to.first);
            }
        }
    }
    cout << "topological ordering:\n";
    for(int x : topo) cout << x << ' ';
    cout << '\n';
    return 0;
}



























