const int Max = 3e5+2;
vector<int> adj[Max], bridgeTree[Max];
bool visited[Max];
int timeIn[Max], currTime = 0, minTime[Max];
vector<pair<int, int> > bridges;

vector<int> p(Max,-1);
int find(int x) {return p[x] < 0 ? x : p[x] = find(p[x]);}
void merge(int x, int y) {
    if((x=find(x)) == (y=find(y))) return;
    if(p[y] < p[x]) swap(x,y);
    p[x] += p[y];
    p[y] = x;
}

void dfs(int node, int prev, int currID = 1) {
    visited[node] = true;
    timeIn[node] = minTime[node] = ++currTime;
    for(int to : adj[node]) {
        if(to != prev) {
            minTime[node] = min(minTime[node], timeIn[to]);
        }
        if(visited[to]) continue;
        dfs(to, node);
        minTime[node] = min(minTime[node], minTime[to]);
        if(minTime[to] > timeIn[node]) {
            bridges.push_back({node, to});
        } else {
            merge(node, to);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) {
        minTime[i] = timeIn[i] = Max;
        visited[i] = false;
    }
    int u, v;
    for(int i = 0; i < m; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    currTime = 0;
    dfs(1,1);
    for(auto &p : bridges) {
        u = find(p.first);
        v = find(p.second);
        bridgeTree[u].push_back(v);
        bridgeTree[v].push_back(u);
    }
    return 0;
}
