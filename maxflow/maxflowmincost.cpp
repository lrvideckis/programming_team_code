// Min cost max flow algorithm using an adjacency matrix.  If you
// want just regular max flow, setting all edge costs to 1 gives
// running time O(|E|^2 |V|).
//
// Running time: O(min(|V|^2 * totflow, |V|^3 * totcost))
//
// INPUT: cap -- a matrix such that cap[i][j] is the capacity of
//               a directed edge from node i to node j
//
//        cost -- a matrix such that cost[i][j] is the (positive)
//                cost of sending one unit of flow along a
//                directed edge from node i to node j
//
//        source -- starting node
//        sink -- ending node
//
// OUTPUT: max flow and min cost; the matrix flow will contain
//         the actual flow values (note that unlike in the MaxFlow
//         code, you don't need to ignore negative flow values -- there
//         shouldn't be any)
//
// To use this, create a MinCostMaxFlow object, and call it like this:
//
//   MinCostMaxFlow nf;
//   int maxflow = nf.getflow(cap,cost,source,sink);

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll inf = (ll)1 << 60;

struct MinCostMaxFlow {
    vector<vector<ll>> cap, flow, cost;
    vector<ll> dad, pi;
    ll n;

    ll search(ll source, ll sink) {
        vector<bool> found(n+1, false);
        vector<ll> dist(n+1, inf);
        /*
           Arrays.fill(found, false);
           Arrays.fill(dist, inf);
         */
        dist[source] = 0;

        while (source != n) {
            ll best = n;
            found[source] = true;
            for (ll k = 0; k < n; k++) {
                if (found[k]) continue;
                if (flow[k][source] != 0) {
                    ll val = dist[source] + pi[source] - pi[k] - cost[k][source];
                    if (dist[k] > val) {
                        dist[k] = val;
                        dad[k] = source;
                    }
                }
                if (flow[source][k] < cap[source][k]) {
                    ll val = dist[source] + pi[source] - pi[k] + cost[source][k];
                    if (dist[k] > val) {
                        dist[k] = val;
                        dad[k] = source;
                    }
                }
                if (dist[k] < dist[best]) best = k;
            }
            source = best;
        }
        for (ll k = 0; k < n; k++) {
            pi[k] = min(pi[k] + dist[k], inf);
        }

        return found[sink];
    }


    pair<ll,ll> getflow(vector<vector<ll>> param_cap, vector<vector<ll>> param_cost, ll source, ll sink) {
        cap.clear();
        cost.clear();
        flow.clear();
        dad.clear();
        pi.clear();

        n = param_cap.size();

        cap.resize(n, vector<ll>(n));
        cost.resize(n, vector<ll>(n));
        flow.resize(n, vector<ll>(n,0));

        for(ll i = 0; i < n; i++) {
            for(ll j = 0; j < n; j++) {
                cap[i][j] = param_cap[i][j];
                cost[i][j] = param_cost[i][j];
            }
        }

        dad.resize(n,0);
        pi.resize(n,0);

        ll totflow = 0, totcost = 0;
        while(search(source, sink) > 0) {
            ll amt = inf;
            for(ll x = sink; x != source; x = dad[x])
                amt = min(amt, flow[x][dad[x]] != 0 ? flow[x][dad[x]] :
                        cap[dad[x]][x] - flow[dad[x]][x]);
            for(ll x = sink; x != source; x = dad[x]) {
                if(flow[x][dad[x]] != 0) {
                    flow[x][dad[x]] -= amt;
                    totcost -= amt * cost[x][dad[x]];
                }
                else {
                    flow[dad[x]][x] += amt;
                    totcost += amt * cost[dad[x]][x];
                }
            }
            totflow += amt;
        }

        return {totflow, totcost};
    }
};

int main(){
    MinCostMaxFlow flow;

    vector<vector<ll>> cap =
        {{0, 3, 4, 5, 0},
        {0, 0, 2, 0, 0},
        {0, 0, 0, 4, 1},
        {0, 0, 0, 0, 10},
        {0, 0, 0, 0, 0}};

    vector<vector<ll>> cost1 =
        {{0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}};

    vector<vector<ll>> cost2 =
        {{0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}};

    // should print out:
    //   10 1
    //   10 3

    pair<ll,ll> p1 = flow.getflow(cap, cost1, 0, 4);
    pair<ll,ll> p2 = flow.getflow(cap, cost2, 0, 4);

    cout << p1.first << " " << p1.second << endl;
    cout << p2.first << " " << p2.second << endl;
}
