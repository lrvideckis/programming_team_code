/** @file */
#pragma once
/**
 * @see https://codeforces.com/blog/entry/112755
 * @param tl,tr defines range [tl, tr)
 * @returns split point of range which makes the segment tree a complete
 * binary tree
 */
int split(int tl, int tr) {
    int pw2 = 1 << __lg(tr - tl);
    return min(tl + pw2, tr - pw2 / 2);
}
long long op(long long vl, long long vr) {
    return vl + vr;
}
/**
 * By default, update: range add, query: range sum
 *
 * root is at tree[1]
 * internal nodes are [1, n)
 * leaf nodes are [n, 2 * n), but rotated such that arr[0] is at tree[bit_ceil(unsigned(n))]
 */
struct seg_tree {
    const int N;
    vector<long long> tree, lazy;
    seg_tree(int n) : N(n), tree(2 * N), lazy(N) {}
    seg_tree(const vector<long long>& arr) : N(ssize(arr)), tree(2 * N), lazy(N) {
        rotate_copy(begin(arr), begin(arr) + (N ? 2 * N - (2 << __lg(N)) : 0), end(arr), begin(tree) + N);
        for (int i = N - 1; i >= 1; i--) tree[i] = op(tree[2 * i], tree[2 * i + 1]);
    }
    void apply(long long change, int tl, int tr, int v) {
        tree[v] += (tr - tl) * change;
        if (v < N) lazy[v] += change;
    }
    void push(int tl, int tm, int tr, int v) {
        if (lazy[v]) {
            apply(lazy[v], tl, tm, 2 * v);
            apply(lazy[v], tm, tr, 2 * v + 1);
            lazy[v] = 0;
        }
    }
    /**
     * @param le,ri defines range [le, ri)
     */
    void update(int le, int ri, long long change) {update(le, ri, change, 0, N, 1);}
    void update(int le, int ri, long long change, int tl, int tr, int v) {
        if (ri <= tl || tr <= le) return;
        if (le <= tl && tr <= ri) return apply(change, tl, tr, v);
        int tm = split(tl, tr);
        push(tl, tm, tr, v);
        update(le, ri, change, tl, tm, 2 * v);
        update(le, ri, change, tm, tr, 2 * v + 1);
        tree[v] = op(tree[2 * v], tree[2 * v + 1]);
    }
    /**
     * @param le,ri defines range [le, ri)
     */
    long long query(int le, int ri) {return query(le, ri, 0, N, 1);}
    long long query(int le, int ri, int tl, int tr, int v) {
        if (ri <= tl || tr <= le) return 0;
        if (le <= tl && tr <= ri) return tree[v];
        int tm = split(tl, tr);
        push(tl, tm, tr, v);
        return op(query(le, ri, tl, tm, 2 * v),
                  query(le, ri, tm, tr, 2 * v + 1));
    }
};
