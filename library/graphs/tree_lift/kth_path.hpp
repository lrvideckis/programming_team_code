/** @file */
#pragma once
#include "get_lca.hpp"
/**
 * @param tl,u,v endpoint nodes of path
 * @param k index into path
 * @returns the node vector<int>({u,p[u],..,lca(u,v),..,p[v],v})[k], so u if k=0
 * @time O(log(path length(u, v)))
 * @space O(1)
 */
inline int kth_path(const tree_lift& tl, int u, int v, int k) {
    int lca_d = tl.d[get_lca(tl, u, v)];
    int u_lca = tl.d[u] - lca_d;
    int v_lca = tl.d[v] - lca_d;
    return k <= u_lca ? kth_par(tl, u, k) : kth_par(tl, v, u_lca + v_lca - k);
}
