/** @file */
#pragma once
#include "get_lca.hpp"
/**
 * @param lca,u,v endpoint nodes of path
 * @returns number of edges on path
 * @time O(1)
 * @space O(1)
 */
inline int dist_edges(const LCA& lca, int u, int v) {
    return lca.d[u] + lca.d[v] - 2 * lca.d[get_lca(lca, u, v)];
}
