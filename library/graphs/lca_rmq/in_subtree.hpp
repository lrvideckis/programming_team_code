/** @file */
#pragma once
#include "get_lca.hpp"
/**
 * @param lca lca via rmq
 * @param u,v 2 nodes
 * @returns 1 iff v is in u's subtree
 * @time O(1)
 * @space O(1)
 */
inline bool in_subtree(const LCA& lca, int u, int v) {
    return lca.in[u] <= lca.in[v] && lca.in[v] < lca.in[u] + lca.sub_sz[u];
}
