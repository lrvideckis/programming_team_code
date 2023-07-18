/** @file */
#pragma once
#include "kth_par.hpp"
/**
 * @param tl,u,v 2 nodes in the same component
 * @returns lca of u, v
 * @time O(log(path length(u, v)))
 * @space O(1)
 */
auto lca_lift = [&](int u, int v) -> int {
    if (tl.d[u] < tl.d[v]) swap(u, v);
    u = kth_par(u, tl.d[u] - tl.d[v]);
    while (u != v)
        if (tl.j[u] != tl.j[v]) u = tl.j[u], v = tl.j[v];
        else u = tl.p[u], v = tl.p[v];
    return u;
};
