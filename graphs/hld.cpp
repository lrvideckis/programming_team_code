struct hld {
    int Time=0;
    vector<int> Size, par, timeIn, Next, Depth;
    hld(vector<vector<int>> &adj, int root) :
        Size(adj.size(),1), par(adj.size()), Depth(adj.size(),1), timeIn(adj.size()), Next(adj.size()) {
        dfs1(root,adj);
        dfs2(root,adj);
    }
    void dfs1(int node, vector<vector<int>> &adj) {
        for(auto &to: adj[node]) {
            if(to == par[node]) continue;
            Depth[to] = 1 + Depth[node];
            par[to] = node;
            dfs1(to, adj);
            Size[node] += Size[to];
            if(Size[to] > Size[adj[node][0]] || adj[node][0] == par[node]) {
                swap(to, adj[node][0]);
            }
        }
    }
    void dfs2(int node, vector<vector<int>> &adj) {
        timeIn[node] = Time++;
        for(auto to: adj[node]) {
            if(to == par[node]) continue;
            Next[to] = (Time == timeIn[node]+1 ? Next[node] : to);
            dfs2(to, adj);
        }
    }
    // Returns intervals corresponding to the path between u and v, not necessarily in order
    vector<pair<int, int>> path(int u, int v) const {
        vector<pair<int, int>> res;
        for (;; v = par[Next[v]]) {
            if (timeIn[v] < timeIn[u]) swap(u, v);
            if (timeIn[Next[v]] <= timeIn[u]) {
                res.push_back({timeIn[u], timeIn[v]});
                return res;
            }
            res.push_back({timeIn[Next[v]], timeIn[v]});
        }
    }
    // Returns interval corresponding to the subtree of node i
    pair<int,int> subtree(int i) const {
        return {timeIn[i], timeIn[i] + Size[i] - 1};
    }
    // Returns lca of nodes u and v
    int lca(int u, int v) const {
        for (;; v = par[Next[v]]) {
            if (timeIn[v] < timeIn[u]) swap(u, v);
            if (timeIn[Next[v]] <= timeIn[u]) return u;
        }
    }
};
