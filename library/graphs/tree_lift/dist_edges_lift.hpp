/** @file */
#pragma once
#include "lca_lift.hpp"
/**
 * @param u,v endpoint nodes of path
 * @returns number of edges on path
 * @time O(log(path length(u, v)))
 * @space O(1)
 */
auto dist_edges_lift = [&](int u, int v) -> int {
    return tl.d[u] + tl.d[v] - 2 * tl.d[lca_lift(u, v)];
};
