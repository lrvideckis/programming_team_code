struct twosat {
    int n;
    vector<vector<int> > adj, adjInv;
    vector<int> scc;
    int sccID;
    vector<bool> visited, assignment;

    twosat(int nodes) {
        n = 2*nodes;
        adj.resize(n);
        adjInv.resize(n);
        scc.resize(n);
        assignment.resize(n/2);
    }
    
    
    //X AND Y = (X OR X) AND (Y OR Y)
    //X NAND Y = (!X OR !Y)
    //X NOR Y = (!X OR !X) AND (!Y OR !Y)
    //X XOR Y = (X OR Y) AND (!X OR !Y)
    //X XNOR Y = (!Y OR X) AND (!X OR Y)
    void add(int i, bool statusI, int j, bool statusJ) {
        const int from1 = i+(!statusI)*(n/2);
        const int to1 = j+statusJ*(n/2);
        adj[from1].push_back(to1);
        adjInv[to1].push_back(from1);
        const int from2 = j+(!statusJ)*(n/2);
        const int to2 = i+statusI*(n/2);
        adj[from2].push_back(to2);
        adjInv[to2].push_back(from2);
    }
    
    void dfs1(int curr, stack<int> &seen) {
        visited[curr] = true;
        for(int x : adj[curr]) {
            if(!visited[x]) {
                dfs1(x, seen);
            }
        }
        seen.push(curr);
    }

    void dfs2(int curr) {
        visited[curr] = true;
        scc[curr] = sccID;
        for(int x : adjInv[curr]) {
            if(!visited[x]) {
                dfs2(x);
            }
        }
    }

    bool solve() {
        visited.resize(n+1,false);
        stack<int> seen;
        for(int i = 0; i < n; ++i) {
            if(!visited[i]) {
                dfs1(i, seen);
            }
        }
        visited.clear();
        visited.resize(n+1,false);
        sccID = 0;
        while(!seen.empty()) {
            while(!seen.empty() && visited[seen.top()]) seen.pop();
            if(!seen.empty()) {
                dfs2(seen.top());
                sccID++;
            }
        }
        for(int i = 0; i < n/2; ++i) {
            if(scc[i] == scc[i+n/2]) {
                return false;
            }
            assignment[i] = scc[i] < scc[i+n/2];
        }
        return true;
    }
};
