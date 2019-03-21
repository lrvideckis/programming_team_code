// Implementation of Hopcroft-Karp algorithm
struct BipartiteMatcher {
    vector<vector<int>> G;
    vector<int> L, R, Viz;
    vector<bool> visitedA, visitedB;
    BipartiteMatcher(int n, int m) :
        G(n), L(n, -1), R(m, -1), Viz(n), visitedA(n), visitedB(m) {}

    void AddEdge(int a, int b) {
        G[a].push_back(b);
    }

    bool Match(int node) {
        if(Viz[node]) 
            return false;
        Viz[node] = true;
        for(auto vec : G[node]) {
            if(R[vec] == -1 || Match(R[vec])) {
                L[node] = vec;
                R[vec] = node;
                return true;
            }
        }
        return false;
    }
    int Solve() {
        bool ok = true;
        while(ok) {
            ok = false;
            fill(Viz.begin(), Viz.end(), 0);
            for(int i = 0; i < L.size(); ++i)
                if(L[i] == -1)
                    ok |= Match(i);
        }
        
        int ret = 0;
        for(int i = 0; i < L.size(); ++i)
            ret += (L[i] != -1);
        return ret;
    }
    void dfs(int node) {
        visitedA[node] = true;
        for(auto to : G[node]) {
            if(!visitedB[to] && R[to] != -1) {
                visitedB[to] = true;
                dfs(R[to]);
            }
        }
    }
    //returns all the nodes in the min vertex cover
    //O(time to find max matching) + O(n)
    //first vector: all nodes in the cover on the left side
    //second vector: all nodes in the cover on the right side
    pair<vector<int>, vector<int>> getMinVertexCover() {
        Solve();
        for(int i = 0; i < L.size(); ++i) {
            if(L[i] == -1) {
                dfs(i);
            }
        }
        pair<vector<int>, vector<int>> cover;
        for(int i = 0; i < L.size(); ++i) {
            if(!visitedA[i]) cover.first.push_back(i);
        }
        for(int i = 0; i < R.size(); ++i) {
            if(visitedB[i]) cover.second.push_back(i);
        }
        return cover;
    }
};
