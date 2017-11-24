#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
#define int long long
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define endl '\n'
#define D(x) cout<<#x<<" -> "<<x<<'\n'
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define uni(x) (x).erase(unique(all(x)), (x).end());
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define rep1(i, n) for (int i = 1; i <= (int)(n); ++i)
const ll infll = powl(2, 62)-1;
const ld pi = 4.0*atanl(1.0);
const int mod = powl(10, 9) + 7;

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
	tree[node] = max(tree[node*2], tree[node*2+1]);
}
void build() {
	memset(lazy, 0, sizeof lazy);
    build(1,0,arr.size()-1);
}

void update(int node, int a, int b, int i, int j, int value) {
  	if(lazy[node] != 0) {
   		tree[node] += lazy[node];
		if(a != b) {
			lazy[node*2] += lazy[node];
    			lazy[node*2+1] += lazy[node];
		}
   		lazy[node] = 0;
  	}
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
	tree[node] = max(tree[node*2], tree[node*2+1]);
}
void update(int i, int j, int value) {
    update(1,0,arr.size()-1,i,j,value);
}

int query(int node, int a, int b, int i, int j) {
	if(a > b || a > j || b < i) return -inf;
	if(lazy[node] != 0) {
		tree[node] += lazy[node];
		if(a != b) {
			lazy[node*2] += lazy[node];
			lazy[node*2+1] += lazy[node];
		}
		lazy[node] = 0;
	}
	if(a >= i && b <= j)
		return tree[node];
	int q1 = query(node*2, a, (a+b)/2, i, j);
	int q2 = query(1+node*2, 1+(a+b)/2, b, i, j);
	int res = max(q1, q2);
	return res;
}
int query(int i, int j) {
    return query(1,0,arr.size()-1,i,j);
}

int32_t main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n, d;
    cin >> n >> d;
    arr.resize(n+1,0);
    build();
    int sum = 0;
    int i = 1;
    for(int &x : arr) {
        cin >> x;
        sum += x;
        update(i,i,sum);
        if(sum > d) {
            cout << "-1\n";
            return 0;
        }
        i++;
    }
    int counter = 0;
    //rep1(i,n) cout << query(i,i) << ' ';cout << '\n';
    rep1(i,n) {
        if(query(i,i) > d) {
            cout << "-1\n";
            return 0;
        }
        if(arr[i-1] == 0) {
            if(query(i,n) > d) {
                cout << "-1\n";
                return 0;
            }
            if(query(i,i) < 0) {
                int largest = query(i,n);
                update(i,n, d-largest);
                int q = query(i,i);
                if(q > d || q < 0) {
                    cout << "-1\n";
                    return 0;
                }
                counter++;
            }
        }
    }
    cout << counter << '\n';
    return 0;
}


















