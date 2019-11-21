struct Node {
    ll sum = 0;
    ll mx = 0;
    ll mn = 0;
};

struct SegmentTree {
    vector<Node> tree;
    vector<ll> lazy;
    int n, root, size;
    const ll inf = 1e18;
    const Node zero = {0, -inf, inf};
    SegmentTree(int currSize) : n((int)currSize), root(1) {
        ll x = (ll)(ceil(log2(currSize)));
        size = (int)(2*(ll)pow(2, x));
        tree.resize(size);
        lazy.resize(size, 0);
    }
    SegmentTree(const vector<ll> &arr) : n((int)arr.size()), root(1) {
        ll x = (ll)(ceil(log2(n)));
        size = (int)(2*(ll)pow(2, x));
        tree.resize(size);
        lazy.resize(size, 0);
        build(arr, root, 0, n-1);
    }
    Node combine(const Node &L, const Node &R) {
        Node par;
        par.sum = L.sum + R.sum;
        par.mx = max(L.mx, R.mx);
        par.mn = min(L.mn, R.mn);
        return par;
    }
    void build(const vector<ll> &arr, int node, int start, int end) {
        if(start == end) {
            tree[node].sum = arr[start];
            tree[node].mx = arr[start];
            tree[node].mn = arr[start];
        } else {
            int mid = (start+end)/2;
            build(arr, 2*node, start, mid);
            build(arr, 2*node+1, mid+1, end);
            tree[node] = combine(tree[2*node], tree[2*node+1]);
        }
    }
    void pendingUpdate(int node, int start, int end) {
        ll &currLazy = lazy[node];
        if(currLazy) {
            tree[node].sum += (end-start+1) * currLazy;
            tree[node].mx += currLazy;
            tree[node].mn += currLazy;
            if(start != end) {
                lazy[2*node] += currLazy;
                lazy[2*node+1] += currLazy;
            }
            currLazy = 0;
        }
    }
    void updateRange(int l, int r, ll diff) {updateRange(root, 0, n-1, l, r, diff);}
    void updateRange(int node, int start, int end, int l, int r, ll diff) {
        pendingUpdate(node, start, end);
        if(start > end || start > r || end < l) return;
        if(start >= l && end <= r) {
            tree[node].sum += (end-start+1) * diff;
            tree[node].mx += diff;
            tree[node].mn += diff;
            if(start != end) {
                lazy[2*node] += diff;
                lazy[2*node+1] += diff;
            }
            return;
        }
        int mid = (start + end) / 2;
        updateRange(2*node, start, mid, l, r, diff);
        updateRange(2*node+1, mid+1, end, l, r, diff);
        tree[node] = combine(tree[2*node], tree[2*node+1]);
    }
    Node query(int l, int r) {return query(root, 0, n-1, l, r);}
    Node query(int node, int start, int end, int l, int r) {
        if(r < start || end < l) return zero;
        pendingUpdate(node, start, end);
        if(l <= start && end <= r) return tree[node];
        int mid = (start+end)/2;
        return combine(query(2*node, start, mid, l, r), query(2*node+1, mid+1, end, l, r));
    }
};
