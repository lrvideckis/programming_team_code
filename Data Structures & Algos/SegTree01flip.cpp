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
#define uni(x) (x).erase(unique(all(x)), (x).end());
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define rep1(i, n) for (int i = 1; i <= (int)(n); ++i)
const ll infll = powl(2, 62)-1;
const ld pi = 4.0*atanl(1.0);
const ll mod = powl(10, 9) + 7;

/*queries include flipping bits on a range, summing bits on range*/
struct SegmentTree {
private:
    //change this to max(a, b) for max segment trees
    vector<ll> tree, lazy;
    ll n, root, size;
public:
    SegmentTree(vector<ll> &arr) : n(arr.size()), root(1) {
        ll x = (ll)(ceil(log2(n)));
        size = 2*(ll)pow(2, x);
        tree.resize(size);
        lazy.resize(size);
        build(arr, root, 0, n-1);
    }
    void build(vector<ll> &arr, ll node, ll start, ll end) {
        if(start == end) tree[node] = arr[start];
        else {
            ll mid = (start+end)/2;
            build(arr, 2*node, start, mid);
            build(arr, 2*node+1, mid+1, end);
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }
    void pendingUpdate(ll node, ll start, ll end) {
        if(lazy[node]) {
            if(lazy[node]%2==1) {
                tree[node] = end - start + 1 - tree[node];
            }
            if(start != end) {
                lazy[2*node] += lazy[node];
                lazy[2*node+1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    void updateRange(ll l, ll r) { updateRange(root, 0, n-1, l, r);}
    void updateRange(ll node, ll start, ll end, ll l, ll r) {
        if(start > end) return;
        pendingUpdate(node, start, end);
        if(start > r || end < l) return;
        if(start >= l && end <= r) {
            tree[node] = end - start + 1 - tree[node];
            if(start != end) {
                lazy[2*node]++;
                lazy[2*node+1]++;
            }
            return;
        }
        ll mid = (start + end) / 2;
        updateRange(2*node, start, mid, l, r);
        updateRange(2*node+1, mid+1, end, l, r);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
    ll query(ll l, ll r) { return query(root, 0, n-1, l, r);}
    ll query(ll node, ll start, ll end, ll l, ll r) {
        if(l > r) return 0;
        pendingUpdate(node, start, end);
        if(r < start || end < l) return 0;
        if(l <= start && end <= r) return tree[node];
        ll mid = (start+end)/2;
        return query(2*node, start, mid, l, r) + query(2*node+1, mid+1, end, l, r);
    }
};

void preTrav(vector<vector<int> > &adj, vector<int> &startOfSeg, vector<int> &endOfSeg, int curr, int &size) {
    startOfSeg[curr] = size++;
    for(int child : adj[curr]) {
        preTrav(adj, startOfSeg, endOfSeg, child, size);
    }
    endOfSeg[curr] = size-1;
}

int32_t main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n;
    cin >> n;
    vector<vector<int> > adj(n+1);
    for(int i = 2; i <= n; ++i) {
        int parent;
        cin >> parent;
        //adj[i].pb(parent);
        adj[parent].pb(i);
    }
    vector<int> light(n+1,0);
    vector<int> startOfSeg(n+1,0), endOfSeg(n+1,0), tour;
    int size = 1;
    preTrav(adj, startOfSeg, endOfSeg, 1, size);
    rep1(i,n) {
        int temp;
        cin >> temp;
        light[startOfSeg[i]] = temp;
    }
    int q;
    cin >> q;
    string command;
    int curr;
    SegmentTree st(light);
    while(q--) {
        cin >> command >> curr;
        if(command == "get") {
            cout << st.query(startOfSeg[curr], endOfSeg[curr]) << '\n';
        } else {
            st.updateRange(startOfSeg[curr], endOfSeg[curr]);
        }
//        for(int i
    }
    return 0;
}

































