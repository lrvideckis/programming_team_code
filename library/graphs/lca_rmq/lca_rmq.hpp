/** @file */
#pragma once
#include "constructor.hpp"
/**
 * @param u,v 2 nodes in the same component
 * @returns lca of u, v
 * @time O(1)
 * @space O(1)
 */
auto lca_rmq = [&](int u, int v) -> int {
    if (u == v) return u;
    auto [x, y] = minmax(lca.in[u], lca.in[v]);
    return lca.p[lca.rmq.query(x + 1, y + 1)];
};
