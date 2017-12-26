#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
#define int long long
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define D(x) cout<<#x<<" -> "<<x<<'\n'
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define uni(x) (x).erase(unique(all(x)), (x).end())
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define rep1(i, n) for (int i = 1; i <= (int)(n); ++i)
#define infll 0x7fffffffffffffff
const ld pi = 4.0*atanl(1.0);
const ll mod = powl(10, 9) + 9;


#define MAX (1+(int)(1e6))
#define inf 0x7fffffff

vector<int> arr;
int tree[MAX];
int lazy[MAX];

void build(int node, int a, int b) {
  	if(a > b) return;
  	if(a == b) {
    	tree[node] = arr[a];
		return;
	}
	build(node*2, a, (a+b)/2);
	build(node*2+1, 1+(a+b)/2, b);
	tree[node] = min(tree[node*2], tree[node*2+1]);
}
void build() {
	memset(lazy, 0, sizeof lazy);
    build(1,0,arr.size()-1);
}

void propogate(int node, int a, int b) {
    if(lazy[node] != 0) {
   		tree[node] += lazy[node];
		if(a != b) {
			lazy[node*2] += lazy[node];
    		lazy[node*2+1] += lazy[node];
		}
   		lazy[node] = 0;
  	}
}

void update(int node, int a, int b, int i, int j, int value) {
  	propogate(node, a, b);
	if(a > b || a > j || b < i)
		return;
  	if(a >= i && b <= j) {
    	tree[node] += value;
		if(a != b) {
			lazy[node*2] += value;
			lazy[node*2+1] += value;
		}
    	return;
	}
	update(node*2, a, (a+b)/2, i, j, value);
	update(1+node*2, 1+(a+b)/2, b, i, j, value);
	tree[node] = min(tree[node*2], tree[node*2+1]);
}
void update(int i, int j, int value) {
    update(1,0,arr.size()-1,i,j,value);
}

int query(int node, int a, int b, int i, int j) {
	if(a > b || a > j || b < i) return infll;
  	propogate(node, a, b);
	if(a >= i && b <= j)
		return tree[node];
	int q1 = query(node*2, a, (a+b)/2, i, j);
	int q2 = query(1+node*2, 1+(a+b)/2, b, i, j);
	return min(q1, q2);
}
int query(int i, int j) {
    return query(1,0,arr.size()-1,i,j);
}

int32_t main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n;
    cin >> n;
    arr.resize(n);
    rep(i,n) cin >> arr[i];
    build();
    int l, r;
    string line;
    int m;
    cin >> m;
    cin.ignore();
    while(m--) {
        getline(cin,line);
        vector<string> q = seperate(line);
        int l = stoi(q[0]);
        int r = stoi(q[1]);
        if(q.size() == 3) {
            int diff = stoi(q[2]);
            if(l > r) {
                update(l,n-1,diff);
                update(0,r,diff);
            } else {
                update(l,r,diff);
            }
        } else {
            if(l > r) {
                cout << min(query(l,n-1), query(0,r)) << '\n';
            } else {
                cout << query(l,r) << '\n';
            }
        }
    }
    return 0;
}
































