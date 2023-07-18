/** @file */
#pragma once
#include "constructor.hpp"
/**
 * @param lca,u,v 2 nodes in the same component
 * @returns lca of u, v
 * @time O(1)
 * @space O(1)
 */
inline int get_lca(const LCA& lca, int u, int v) {
    if (u == v) return u;
    auto [x, y] = minmax(lca.in[u], lca.in[v]);
    return lca.p[lca.rmq.query(x + 1, y + 1)];
}
