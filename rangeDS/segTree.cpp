#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SegmentTree {
    vector<ll> tree, lazy;
    ll n, root, size;
    SegmentTree(int currSize) : n(currSize), root(1) {
        ll x = (ll)(ceil(log2(currSize)));
        size = 2*(ll)pow(2, x);
        tree.resize(size, 0);
        lazy.resize(size, 0);
    }
    SegmentTree(vector<ll> &arr) : n(arr.size()), root(1) {
        ll x = (ll)(ceil(log2(n)));
        size = 2*(ll)pow(2, x);
        tree.resize(size);
        lazy.resize(size, 0);
        build(arr, root, 0, n-1);
    }
    void build(vector<ll> &arr, int node, int start, int end) {
        if(start == end) tree[node] = arr[start];
        else {
            ll mid = (start+end)/2;
            build(arr, 2*node, start, mid);
            build(arr, 2*node+1, mid+1, end);
            tree[node] = tree[2*node] + tree[2*node+1];
        }
    }
    void pendingUpdate(int node, int start, int end) {
        if(lazy[node]) {
            tree[node] += (end-start+1) * lazy[node];
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
            tree[node] += (end-start+1) * diff;
            if(start != end) {
                lazy[2*node] += diff;
                lazy[2*node+1] += diff;
            }
            return;
        }
        ll mid = (start + end) / 2;
        updateRange(2*node, start, mid, l, r, diff);
        updateRange(2*node+1, mid+1, end, l, r, diff);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
    ll query(int l, int r) {return query(root, 0, n-1, l, r);}
    ll query(int node, int start, int end, int l, int r) {
        if(r < start || end < l) return 0;
        pendingUpdate(node, start, end);
        if(l <= start && end <= r) return tree[node];
        ll mid = (start+end)/2;
        return query(2*node, start, mid, l, r) + query(2*node+1, mid+1, end, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    srand(time(NULL));
    int n = 1e4;
    vector<ll> arr(n);
    for(int i = 0; i < n; ++i) {
        arr[i] = rand()%1000000;
    }
    SegmentTree st(arr);
    for(int i = 0; i < n; ++i) {
        int L = rand()%n;
        int R = rand()%n;
        if(L > R) swap(L, R);
        if(rand()%2 == 0) {
            int diff = rand()%1000000;
            for(int j = L; j <= R; ++j) {
                arr[j] += (ll)diff;
            }
            st.updateRange(L, R, diff);
        } else {//query
            ll sum = 0;
            for(int j = L; j <= R; ++j) {
                sum += arr[j];
            }
            if(sum != st.query(L, R)) {
                cout << sum << ' ' << st.query(L, R) << '\n';
            } //else cout << "correct\n";
        }
    }
    return 0;
}



















