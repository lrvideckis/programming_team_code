/** @file */
#pragma once
#include "in_subtree.hpp"
/**
 * @see https://codeforces.com/blog/entry/71567?#comment-559285
 * @code{.cpp}
 *     int u, v; //to loop over all nodes (except v) on path from u to v:
 *     for (int i = u; i != v; i = lca.next_on_path(i, v)) {}
 * @endcode
 * @param lca lca via rmq
 * @param u,v endpoint nodes of path
 * @returns the node vector<int>({u,p[u],..,lca(u,v),..,p[v],v})[1]
 * @time O(1)
 * @space O(1)
 */
inline int next_on_path(const LCA& lca, int u, int v) {
    assert(u != v);
    return in_subtree(lca, u, v) ? lca.rmq.query(lca.in[u] + 1, lca.in[v] + 1) : lca.p[u];
}
