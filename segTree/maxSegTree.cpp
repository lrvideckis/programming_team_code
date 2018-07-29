#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SegmentTree {
private:
    //change this to max(a, b) for max segment trees
    vector<ll> tree, lazy;
    ll n, root, size;
public:
    SegmentTree(){}
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
            tree[node] = max(tree[2*node], tree[2*node+1]);
        }
    }
    void pendingUpdate(ll node, ll start, ll end) {
        if(lazy[node]) {
            tree[node] += lazy[node];
            if(start != end) {
                lazy[2*node] += lazy[node];
                lazy[2*node+1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    void update(ll idx, ll diff) { update(root, 0, n-1, idx, diff);}
    void update(ll node, ll start, ll end, ll idx, ll diff) {
        if(start == end) tree[node] += diff;
        else {
            ll mid = (start + end) / 2;
            if(start <= idx && idx <= mid)
                update(2*node, start, mid, idx, diff);
            else update(2*node+1, mid+1, end, idx, diff);
            tree[node] = max(tree[2*node], tree[2*node+1]);
        }
    }
    void updateRange(ll l, ll r, ll diff) { updateRange(root, 0, n-1, l, r, diff);}
    void updateRange(ll node, ll start, ll end, ll l, ll r, ll diff) {
        pendingUpdate(node, start, end);
        if(start > end || start > r || end < l) return;
        if(start >= l && end <= r) {
            tree[node] += diff;
            if(start != end) {
                lazy[2*node] += diff;
                lazy[2*node+1] += diff;
            }
            return;
        }
        ll mid = (start + end) / 2;
        updateRange(2*node, start, mid, l, r, diff);
        updateRange(2*node+1, mid+1, end, l, r, diff);
        tree[node] = max(tree[2*node], tree[2*node+1]);
    }
    ll query(ll l, ll r) { return query(root, 0, n-1, l, r);}
    ll query(ll node, ll start, ll end, ll l, ll r) {
        if(r < start || end < l) return 0;
        pendingUpdate(node, start, end);
        if(l <= start && end <= r) return tree[node];
        ll mid = (start+end)/2;
        return max(query(2*node, start, mid, l, r), query(2*node+1, mid+1, end, l, r));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n = 1e5;
    vector<ll> arr(n);
    for(int i = 0; i < n; ++i) {
        arr[i] = rand()%1000000;
    }
    SegmentTree st(arr);
    for(int i = 0; i < n; ++i) {
        int L = rand()%n;
        int R = rand()%n;
        if(L > R) swap(L, R);
        bool update = (rand()%2 == 0);
        if(update) {
            int diff = rand()%1000000;
            for(int j = L; j <= R; ++j) {
                arr[j] += (ll)diff;
            }
            st.updateRange(L, R, diff);
        } else {//query
            ll largest = arr[L];
            for(int j = L; j <= R; ++j) {
                largest = max(largest, arr[j]);
            }
            if(largest != st.query(L, R)) {
                cout << largest << ' ' << st.query(L, R) << '\n';
            } //else cout << "correct\n";
        }
    }
    
    
    
    
    
    return 0;
}
    
    
    
    /*
    int n, m;
    cin >> n >> m;
    vector<ll> temp(n);
    SegmentTree st[30];
    for(int i = 0; i < 30; ++i) {
        st[i] = SegmentTree(temp);
    }
    vector<int> L(m), R(m), q(m);
    for(int i = 0; i < m; ++i) {
        cin >> L[i] >> R[i] >> q[i];
        L[i]--;
        R[i]--;
        for(int bit = 0; bit < 30; ++bit) {
            if(q[i]&(1<<bit)) {
                st[bit].updateRange(L[i], R[i], 1);
            }
        }
    }
    for(int i = 0; i < m; ++i) {
        int sum = 0;
        for(int bit = 0; bit < 30; ++bit) {
            if(st[bit].query(L[i], R[i]) > 0) {
                sum |= (1<<bit);
            }
        }
        if(sum != q[i]) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    for(int i = 0; i < n; ++i) {
        int sum = 0;
        for(int bit = 0; bit < 30; ++bit) {
            if(st[bit].query(i,i) > 0) {
                sum |= (1<<bit);
            }
        }
        cout << sum << ' ';
    }
    cout << '\n';
    return 0;
}
*/



















