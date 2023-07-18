/** @file */
#pragma once
#include "kth_par.hpp"
/**
 * @param tl,u,v 2 nodes in the same component
 * @returns lca of u, v
 * @time O(log(path length(u, v)))
 * @space O(1)
 */
inline int get_lca(const tree_lift& tl, int u, int v) {
    if (tl.d[u] < tl.d[v]) swap(u, v);
    u = kth_par(tl, u, tl.d[u] - tl.d[v]);
    while (u != v)
        if (tl.j[u] != tl.j[v]) u = tl.j[u], v = tl.j[v];
        else u = tl.p[u], v = tl.p[v];
    return u;
}
