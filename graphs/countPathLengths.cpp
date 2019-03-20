#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef complex<double> cd;

const double PI=acos(-1);
typedef complex<double> base;
inline void fft (vector<base> & a, bool invert) {
	int n=(int) a.size();
	for (int i=1, j=0; i<n; ++i) {
		int bit=n>>1;
		for (;j>=bit;bit>>=1)
			j-=bit;
		j+=bit;
		if(i<j)
			swap(a[i],a[j]);
	}
	for (int len=2; len<=n; len<<=1) {
		double ang = 2*PI/len * (invert ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for (int i=0; i<n; i+=len) {
			base w(1);
			for (int j=0; j<len/2; ++j) {
				base u=a[i+j], v=a[i+j+len/2]*w;
				a[i+j]=u+v;
				a[i+j+len/2]=u-v;
				w*=wlen;
			}
		}
	}
	if (invert)
		for(int i=0;i<n;++i)
			a[i]/=n;
}

// a, b => coefs to multiply,  res => resulting coefs
// a[0], b[0], res[0] = coef x^0
inline void multiply (const vector<int> & a, const vector<int> & b, vector<int> & res) {
    if(a.size() * b.size() <= 256) {
		res.resize(a.size() + b.size(), 0);
		for(int i = 0; i < (int)a.size(); i++)
			for(int j = 0; j < (int)b.size(); j++)
				res[i + j] += 1LL * a[i] * b[j];
		return;
	}
	vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	size_t n=1;
	while (n<max(a.size(),b.size())) n<<=1;
	n<<=1;
	fa.resize(n),fb.resize(n);
	fft (fa,false);  fft(fb,false);
	for (size_t i=0; i<n; ++i)
		fa[i]*=fb[i];
	fft (fa, true);
	res.resize (n);
	for(size_t i=0; i<n; ++i)
		res[i]=(int)(fa[i].real()>0 ? fa[i].real()+0.5 : fa[i].real()-0.5);
}

const int Max = 1e6+10;
int n, sizes[Max];
vector<int> adj[Max], cntPathLength[Max];
ll prod[Max], cntTotalPathLengths[Max] = {0}, cntTotalPathLengthsNaive[Max] = {0};
bool removed[Max];

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
            vector<int> prod;
            multiply(temp, cntPathLength[to], prod);
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
