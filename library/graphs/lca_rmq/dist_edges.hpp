/** @file */
#pragma once
#include "get_lca.hpp"
/**
 * @param lca,u,v endpoint nodes of path
 * @returns number of edges on path
 * @time O(1)
 * @space O(1)
 */
auto dist_edges = [&](int u, int v) -> int {
    return lca.d[u] + lca.d[v] - 2 * lca.d[lca_rmq(u, v)];
};
