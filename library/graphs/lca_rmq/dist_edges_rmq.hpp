/** @file */
#pragma once
#include "lca_rmq.hpp"
/**
 * @param u,v endpoint nodes of path
 * @returns number of edges on path
 * @time O(1)
 * @space O(1)
 */
auto dist_edges_rmq = [&](int u, int v) -> int {
    return lca.d[u] + lca.d[v] - 2 * lca.d[lca_rmq(u, v)];
};
