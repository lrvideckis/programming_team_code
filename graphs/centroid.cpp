const int Max = 2e5+2;
vector<int> adj[Max];
int sizes[Max], parent[Max];
bool removed[Max];

void dfs2(int node, int par) {
    sizes[node] = 1;
    for(int to : adj[node]) {
        if(to != par && !removed[to]) {
            dfs2(to, node);
            sizes[node] += sizes[to];
        }
    }
}

int findCentroid(int node) {
    dfs2(node, node);
    bool found = true;
    int sizeCap = sizes[node]/2;
    int par = node;
    while(found) {
        found = false;
        for(int to : adj[node]) {
            if(to != par && !removed[to] && sizes[to] > sizeCap) {
                found = true;
                par = node;
                node = to;
                break;
            }
        }
    }
    return node;
}

void dfs1(int node, int par) {
    removed[node] = true;
    parent[node] = par;
    for(int to : adj[node]) {
        if(!removed[to]) {
            dfs1(findCentroid(to), node);
        }
    }
}
//dfs1(findCentroid(1), 0);
