const int Max = 1e5+2;
vector<int> adj[Max];
bool visited[Max], cutNode[Max];
int timeIn[Max], currTime = 0, minTime[Max];

void dfs(int node, int prev) {
    visited[node] = true;
    timeIn[node] = minTime[node] = ++currTime;
    int numChildren = 0;
    for(int to : adj[node]) {
        if(to != prev) {
            minTime[node] = min(minTime[node], timeIn[to]);
        }
        if(visited[to]) continue;
        numChildren++;
        if(node == prev && numChildren > 1) {
            cutNode[node] = true;
        }
        dfs(to, node);
        minTime[node] = min(minTime[node], minTime[to]);
        if(node != prev && minTime[to] >= timeIn[node]) {
            cutNode[node] = true;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < Max; ++i) {
        minTime[i] = timeIn[i] = Max;
        visited[i] = cutNode[i] = false;
    }
    int u, v;
    for(int i = 0; i < m; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    currTime = 0;
    for(int i = 0; i < n; ++i) {
        if(!visited[i]) {
            dfs(i,i);
        }
    }
    for(int i = 0; i < n; ++i) {
        if(cutNode[i]) {

        }
    }
    return 0;
}
