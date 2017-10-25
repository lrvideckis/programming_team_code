unordered_map<string, vector<string> > adjList;
unordered_map<string, bool> visited;
unordered_map<string, string> previous;

void dfs(string v) {
    visited[v] = true;
    for(int i = 0; i < adjList[v].size(); i++) {
        if(!visited[adjList[v][i]]) {
            dfs(adjList[v][i], end);
            previous[adjList[v][i]] = v;
        }
    }
}
