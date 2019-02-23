#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct TWOSAT {
    int n;
    vector<set<int> > adj, adjInv;
    vector<int> scc;
    int sccID;
    vector<bool> visited;

    TWOSAT(int nodes) {
        n = 2*nodes;
        adj.resize(n);
        adjInv.resize(n);
        scc.resize(n);
    }
    
    void add(int i, bool statusI, int j, bool statusJ) {
        int from1 = i+(!statusI)*(n/2);
        int to1 = j+statusJ*(n/2);
        adj[from1].insert(to1);
        adjInv[to1].insert(from1);
        int from2 = j+(!statusJ)*(n/2);
        int to2 = i+statusI*(n/2);
        adj[from2].insert(to2);
        adjInv[to2].insert(from2);
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
        }
        return true;
    }
};

signed main() {
    
}































