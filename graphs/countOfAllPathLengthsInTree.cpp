#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef complex<double> cd;

const int Max = 1e6+10;
int n, logBound, bound, a[Max] = {0}, b[Max] = {0}, sizes[Max], perm[Max];
const double pi = 4*atan(1.0);
cd root[Max], arrA[Max], arrB[Max];
vector<int> adj[Max], cntPathLength[Max];
ll prod[Max], cntTotalPathLengths[Max] = {0}, cntTotalPathLengthsNaive[Max] = {0};
bool removed[Max];

void fft(cd* arr) {
    for(int i = 0; i < bound; i++) {
        if(i < perm[i]) {
            swap(arr[i], arr[perm[i]]);
        }
    }
    for(int len = 1; len < bound; len *= 2) {
        for(int pos = 0; pos < bound; pos += 2 * len) {
            for(int i = 0; i < len; i++) {
                cd x = arr[pos + i], y = arr[pos + i + len] * root[bound / len / 2 * i];
                arr[pos + i] = x + y;
                arr[pos + i + len] = x - y;
            }
        }
    }
}

void preCalc() {
    int hb = -1;
    root[0] = 1;
    double angle = 2 * pi / bound;
    for(int i = 1; i < bound; i++) {
        if((i & (i - 1)) == 0) hb++;
        root[i] = cd(cos(angle * i), sin(angle * i));
        perm[i] = perm[i ^ (1 << hb)] + (1 << (logBound - hb - 1));
    }
}

void mult(vector<int> &a, vector<int> &b, vector<ll> &c) {
    logBound = 0;
    while((1<<logBound) < a.size() || (1<<logBound) < b.size()) logBound++;
    logBound++;
    bound = (1<<logBound);
    preCalc();
    for(int i = 0; i < a.size(); i++) {
        arrA[i] = cd(a[i], 0);
    }
    for(int i = a.size(); i < bound; i++) {
        arrA[i] = cd(0, 0);
    }
    for(int i = 0; i < b.size(); i++) {
        arrB[i] = cd(b[i], 0);
    }
    for(int i = b.size(); i < bound; i++) {
        arrB[i] = cd(0, 0);
    }
    fft(arrA);
    fft(arrB);
    for(int i = 0; i < bound; i++) {
        arrA[i] *= arrB[i];
    }
    fft(arrA);
    reverse(arrA + 1, arrA + bound);
    c.resize(bound);
    for(int i = 0; i < bound; i++) {
        arrA[i] /= bound;
        ll temp = (arrA[i].real() > 0 ? arrA[i].real()+.5 : arrA[i].real() - .5);
        c[i] = temp;
    }
    while(c.size() && c.back() == 0) c.pop_back();
}

void dfs2(int node, int par, int root, int currDist) {
    if(cntPathLength[root].size() <= currDist) {
        cntPathLength[root].push_back(0);
    }
    cntPathLength[root][currDist]++;
    sizes[node] = 1;
    for(int to : adj[node]) {
        if(to != par && !removed[to]) {
            dfs2(to, node, root, currDist+1);
            sizes[node] += sizes[to];
        }
    }
}

int findCentroid(int node) {
    dfs2(node, node, node, 1);
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
    int maxLength = 1;
    for(int to : adj[node]) {
        if(to != par && !removed[to]) {
            cntPathLength[to].clear();
            cntPathLength[to].push_back(0);
            dfs2(to, to, to, 1);
            maxLength = max(maxLength, (int)cntPathLength[to].size());
        }
    }
    vector<int> temp(maxLength, 0);
    temp[0]++;
    for(int to : adj[node]) {
        if(to != par && !removed[to]) {
            vector<ll> prod;
            mult(temp, cntPathLength[to], prod);
            for(int i = 0; i < prod.size(); ++i) {
                cntTotalPathLengths[i] += prod[i];
            }
            for(int i = 0; i < cntPathLength[to].size(); ++i) {
                temp[i] += cntPathLength[to][i];
            }
        }
    }
    
    for(int to : adj[node]) {
        if(to != par && !removed[to]) {
            dfs1(findCentroid(to), node);
        }
    }
}

void dfsNaive(int node, int par, int Dist) {
    cntTotalPathLengthsNaive[Dist]++;
    for(int to : adj[node]) {
        if(to == par) continue;
        dfsNaive(to, node, Dist+1);
    }
}

/*
input format:
n = number of nodes
n-1 lines follow: each containing an edge between node u, and node v
forming a tree:
1 <= u, v <= n

sample:
4
1 2
2 3
3 4

*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    preCalc();
    cin >> n;
    int u, v;
    for(int i = 0; i < n-1; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    /*naive version: dfs from every node, and count the number of
    paths of each distance from that starting node*/
    for(int i = 1; i <= n; ++i) {
        dfsNaive(i,i,0);
    }
    int start = findCentroid(1);
    cntPathLength[1].clear();
    dfs1(start, 0);
    for(int i = 1; i < n; ++i) {
        if(cntTotalPathLengthsNaive[i]/2 == 0) break;
        cout << i << ' ' << cntTotalPathLengthsNaive[i]/2 << ' ' << cntTotalPathLengths[i] << '\n';
    }
    return 0;
}


