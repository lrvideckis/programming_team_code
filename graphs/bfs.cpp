void bfs(vector<vector<int> > &adj, vector<int> &dist, int s) {
    dist.resize(adj.size());
    vector<bool> marked(adj.size(), false);
    //vector<int> prev(adj.size());
    queue<int> q;
    q.push(s);
    marked[s] = true;
    dist[s] = 0;
    //prev[s] = s;
    while(!q.empty()) {
        s = q.front();
        q.pop();
        for(int x : adj[s]) {
            if(!marked[x]) {
                q.push(x);
                marked[x] = true;
                dist[x] = dist[s] + 1;
                //prev[x] = s;
            }
        }
    }
}

