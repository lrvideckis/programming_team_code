#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define D(x) cout<<#x<<" -> "<<x<<'\n'
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define uni(x) (x).erase(unique(all(x)), (x).end())
#define rep(i, n) for (ll i = 0; i < (ll)(n); ++i)
#define rep1(i, n) for (ll i = 1; i <= (ll)(n); ++i)
const ld pi = 4.0*atanl(1.0);
const ll infll = (ll)(1e18) + 10;
const ll mod = powl(10, 9) + 7;

int n,m,foundat=1;
vector<vector<int> > adj,scc;//default 1-based indexing
vector<int> disc,low; // init disc to -1
vector<bool> onstack; //init to 0 

void tarjan(int u) {
    static stack<int> st;
    disc[u] = low[u] = foundat++;
    st.push(u);
    onstack[u] = true;
    for(auto i : adj[u]) {
        if(disc[i] == -1){
            tarjan(i);
            low[u] = min(low[u], low[i]);
        } else if(onstack[i]) {
            low[u] = min(low[u], disc[i]);
        }
    }
    if(disc[u] == low[u]) {
        vector<int>  scctem;
        while(true) {
            int v = st.top();
            st.pop();
            onstack[v] = false;
            scctem.pb(v);
            if(u==v) break;
        }
        scc.pb(scctem);
    }
}

//removed '#define ll long long', keep in mind overflow
int main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    adj.resize(n+1);
    disc.resize(n+1,-1);
    low.resize(n+1);
    onstack.resize(n+1,false);
    //input graph here
    rep1(i,n) {
        if(disc[i]==-1) {
            tarjan(i);
        }
    }

    return 0;
}

















