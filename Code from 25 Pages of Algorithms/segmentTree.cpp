#define _USE_MATH_DEFINES//M_PI
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
typedef long long ll;
typedef long double ld;

struct SegmentTree {
private:
    //change this to max(a, b) for max segment trees
    ll function(ll a, ll b) { return a+b; }
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
            tree[node] = function(tree[2*node], tree[2*node+1]);
        }
    }
    void pendingUpdate(ll node, ll start, ll end) {
        if(lazy[node]) {
            tree[node] += (end - start + 1) * lazy[node];
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
            tree[node] = function(tree[2*node], tree[2*node+1]);
        }
    }
    void updateRange(ll l, ll r, ll diff) { updateRange(root, 0, n-1, l, r, diff);}
    void updateRange(ll node, ll start, ll end, ll l, ll r, ll diff) {
        if(start > end || start > r || end < l) return;
        pendingUpdate(node, start, end);
        if(start >= l && end <= r) {
            tree[node] += (end - start + 1) * diff;
            if(start != end) {
                lazy[2*node] += diff;
                lazy[2*node+1] += diff;
            }
            return;
        }
        ll mid = (start + end) / 2;
        updateRange(2*node, start, mid, l, r, diff);
        updateRange(2*node+1, mid+1, end, l, r, diff);
        tree[node] = function(tree[2*node], tree[2*node+1]);
    }
    ll query(ll l, ll r) { return query(root, 0, n-1, l, r);}
    ll query(ll node, ll start, ll end, ll l, ll r) {
        if(r < start || end < l) return 0;
        pendingUpdate(node, start, end);
        if(l <= start && end <= r) return tree[node];
        ll mid = (start+end)/2;
        return function(query(2*node, start, mid, l, r), query(2*node+1, mid+1, end, l, r));
    }
};


int main() {
    vector<ll> arr;
    SegmentTree tree(arr);
    return 0;
}
