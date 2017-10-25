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

int row, col;

struct Graph {
    int V;
    list< pair<int, int> > *adj;
    vector<int> dist;
public:
    int getDist(int V) {
        return dist[V];
    }
    Graph(int V) {
        this->V = V;
        adj = new list<pair<int, int> >[V];
    }
    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));//comment this out for undirected graph
    }
    void shortestPath(int start) {
        set< pair<int, int> > setds;
        dist.resize(V, infll);
        setds.insert(mp(0, start));
        dist[start] = 0;
        while (!setds.empty()) {
            pair<int, int> tmp = *(setds.begin());
            setds.erase(setds.begin());
            int u = tmp.second;
            list< pair<int, int> >::iterator i;
            for (i = adj[u].begin(); i != adj[u].end(); ++i) {
                int v = (*i).first;
                int weight = (*i).second;
                if (dist[v] > dist[u] + weight)
                {
                    if (dist[v] != infll)
                        setds.erase(setds.find(make_pair(dist[v], v)));
                    dist[v] = dist[u] + weight;
                    setds.insert(make_pair(dist[v], v));
                }
            }
        }
    }
};

int32_t main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    
    return 0;
}















