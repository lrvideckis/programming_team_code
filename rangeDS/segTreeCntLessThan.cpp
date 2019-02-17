#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SegmentTree {
private:
    vector<ll> lazy;//, added;
    vector<vector<ll>> tree;
    
    ll n, root, size;
public:
    SegmentTree(vector<ll> &arr) : n(arr.size()), root(1) {
        ll x = (ll)(ceil(log2(n)));
        size = 2*(ll)pow(2, x);
        tree.resize(size);
        lazy.resize(size, 0);
        //added.resize(size, 0);
        build(arr, root, 0, n-1);
    }
    void build(vector<ll> &arr, int node, int start, int end) {
        if(start == end) tree[node].push_back(arr[start]);
        else {
            ll mid = (start+end)/2;
            build(arr, 2*node, start, mid);
            build(arr, 2*node+1, mid+1, end);
            tree[node] = tree[2*node];
            for(ll num : tree[2*node+1]) {
                tree[node].push_back(num);
            }
            sort(tree[node].begin(), tree[node].end());//TODO: optimize this to linear merge like in merge sort
        }
    }
    void pendingUpdate(int node, int start, int end) {
        if(lazy[node]) {
            
            for(ll &num : tree[node]) num += lazy[node];
            //added[node] += lazy[node];
            if(start != end) {
                lazy[2*node] += lazy[node];
                lazy[2*node+1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    void updateRange(int l, int r, ll diff) {updateRange(root, 0, n-1, l, r, diff);}
    void updateRange(int node, int start, int end, int l, int r, ll diff) {
        pendingUpdate(node, start, end);
        if(start > end || start > r || end < l) return;
        if(start >= l && end <= r) {
            //added[node] += diff;
            //lazy[node] += diff;
            for(ll &num : tree[node]) num += diff;
            if(start != end) {
                lazy[2*node] += diff;
                lazy[2*node+1] += diff;
            }
            return;
        }
        ll mid = (start + end) / 2;
        updateRange(2*node, start, mid, l, r, diff);
        updateRange(2*node+1, mid+1, end, l, r, diff);
        //tree[node] = tree[2*node] + tree[2*node+1];
    }
    int query(int l, int r, ll value) {return query(root, 0, n-1, l, r, value);}
    int query(int node, int start, int end, int l, int r, ll value) {
        if(r < start || end < l) return 0;
        pendingUpdate(node, start, end);
        if(l <= start && end <= r) {
            cout << "tree node: " << start << " - " << end << '\n';
            for(int num : tree[node]) cout << num << ' ';cout << '\n';
            return (lower_bound(tree[node].begin(), tree[node].end(), value) - tree[node].begin());
            //return tree[node];
        }
        ll mid = (start+end)/2;
        return query(2*node, start, mid, l, r, value) + query(2*node+1, mid+1, end, l, r, value);
    }
};




int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    const int n = 7, maxn = 100;
    //srand(time(NULL));
    srand(10930);
    vector<ll> arr(n);
    for(int i = 0; i < n; ++i) {
        arr[i] = rand()%maxn;
    }
    cout << "arr:\n";
    for(int i = 0; i < n; ++i) {
        cout << arr[i] << ' ';
    }
    cout << '\n';
    SegmentTree sb(arr);
    for(int i = 0; i < n; ++i) {
        int type = rand()%2;
        int l = rand()%n;
        int r = rand()%n;
        if(l > r) swap(l,r);
        int value = rand()%maxn-maxn/2;
        if(type == 0) {//query
            cout << "query: " << l << ' ' << r << ' ' << value << '\n';
            int naive = 0;
            for(int j = l; j <= r; ++j) {
                if(arr[j] < value) naive++;
            }
            int temp = sb.query(l, r, value);
            if(naive != temp) {
                cout << "incorrect\t" << naive << ' ' << temp << '\n';
            } else cout << "correct\n";
        } else {//update
            cout << "update: " << l << ' ' << r << ' ' << value << '\n';
            for(int j = l; j <= r; ++j) {
                arr[j] += value;
            }
            sb.updateRange(l, r, value);
        }
        cout << "arr:\n";
        for(int i = 0; i < n; ++i) {
            cout << arr[i] << ' ';
        }
        cout << '\n';
        cout << '\n';
    }
    return 0;
}














