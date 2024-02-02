#pragma once
#include "../../library/monotonic_stack/cartesian_k_ary_tree.hpp"
#include "../../library/data_structures/rmq.hpp"
#include "../../library/data_structures/uncommon/linear_rmq.hpp"
tuple<int, vector<vector<int>>, vector<int>> min_cartesian_tree(const vector<int>& a, const vector<int>& le, const vector<int>& ri) {
    int n = ssize(a);
    assert(ssize(le) == n && ssize(ri) == n);
    auto leftmost_min = [&](int i) -> bool {return le[i] == -1 || a[le[i]] < a[i];};
    vector<int> to_min(n);
    iota(begin(to_min), end(to_min), 0);
    for (int i = 0; i < n; i++)
        if (!leftmost_min(i))
            to_min[i] = to_min[le[i]];
    vector<vector<int>> adj(n);
    int root = -1;
    for (int i = 0; i < n; i++) {
        if (le[i] == -1 && ri[i] == n) {
            assert(root == -1);
            root = i;
        } else if (leftmost_min(i)) {
            bool le_par = (le[i] >= 0 && (ri[i] == n || a[le[i]] > a[ri[i]]));
            adj[to_min[le_par ? le[i] : ri[i]]].push_back(i);
        }
    }
    return {root, adj, to_min};
}
void mono_st_asserts(const vector<int>& a) {
    vector<function<bool(int, int)>> compares;
    compares.push_back(less());
    compares.push_back(less_equal());
    compares.push_back(greater());
    compares.push_back(greater_equal());
    int n = ssize(a);
    for (auto cmp : compares) {
        vector<int> init(n);
        iota(begin(init), end(init), 0);
        RMQ rmq(init, [&](int x, int y) -> int { return cmp(a[x], a[y]) ? x : y; });
        linear_rmq lin_rmq(a, cmp);
        auto ri = mono_st(a, cmp), le = mono_range(ri), p = cart_binary_tree(ri);
        {
            int iterations = 0;
            queue<array<int, 3>> q;
            q.push({0, n, n}); // node_le, node_ri, parent
            while(!empty(q)) {
                auto [node_le, node_ri, node_par] = q.front();
                q.pop();
                if (node_le == node_ri) continue;
                iterations++;
                int idx_root = rmq.query(node_le, node_ri);
                int idx_root_2 = lin_rmq.query_idx(node_le, node_ri - 1);
                assert(idx_root == idx_root_2);
                assert(node_le <= idx_root && idx_root < node_ri);
                assert(le[idx_root] == node_le - 1);
                assert(ri[idx_root] == node_ri);
                assert(p[idx_root] == node_par);
                q.push({node_le, idx_root, idx_root});
                q.push({idx_root + 1, node_ri, idx_root});
            }
            assert(iterations == n);
        }
        {
            vector old_way_le = mono_st<int>({rbegin(a), rend(a)}, [&](int x, int y) {return !cmp(y, x);});
            reverse(begin(old_way_le), end(old_way_le));
            transform(begin(old_way_le), end(old_way_le), begin(old_way_le), [&](int i) {return ssize(a) - i - 1;});
            assert(le == old_way_le);
        }
        int iterations = 0;
        for (int i = n - 1; i >= 0; i--) {
            assert(i < ri[i] && ri[i] <= n);
            assert(ri[i] == n || !cmp(a[i], a[ri[i]]));
            for (int j = i + 1; j != ri[i]; j = ri[j]) {
                // for all k in [j, ri[j]): cmp(a[i], a[k])
                // these ranges are disjoint, and union to [i + 1, ri[i])
                assert(j <= ri[i]);
                assert(cmp(a[i], a[j]));
                assert(cmp(a[i], a[ri[j] - 1]));
                assert(cmp(a[i], a[j + (ri[j] - j) / 2]));
                int range_op = a[rmq.query(j, ri[j])];
                assert(cmp(a[i], range_op));
                iterations++;
            }
        }
        // clear the stack
        for (int j = 0; j != n; j = ri[j]) iterations++;
        assert(iterations == n);
    }
    // test cartesian tree against old method
    auto ri = mono_st(a, less_equal()), le = mono_range(ri), p = cart_k_ary_tree(a, ri);
    assert(count(begin(p), end(p), n) == !empty(a));
    for(int i = 0; i < n; i++)
        assert(0 <= p[i] && p[i] <= n && p[i] != i);
    auto [root, adj, to_min] = min_cartesian_tree(a, le, ri);
    vector<int> p_old_method(n, -1);
    auto set_val = [&](int i, int val) -> void {
        assert(p_old_method[i] == -1);
        p_old_method[i] = val;
    };
    assert((root == -1) == empty(a));
    if (root != -1) set_val(root, n);
    for(int i = 0; i < n; i++)
        for(int j : adj[i]) set_val(j, i);
    for(int i = 0; i < n; i++)
        if(to_min[i] < i) set_val(i, to_min[i]);
    assert(p == p_old_method);
}
