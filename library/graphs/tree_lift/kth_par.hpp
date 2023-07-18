/** @file */
#pragma once
#include "constructor.hpp"
tree_lift tl(adj);
/**
 * @param u query node
 * @param k number of edges
 * @returns a node k edges up from u. With k=1, this returns u's parent.
 * @time O(log k)
 * @space O(1)
 */
auto kth_par = [&](int u, int k) -> int {
    if (k > tl.d[u]) return -1;
    int anc_d = tl.d[u] - k;
    while (tl.d[u] > anc_d) u = tl.d[tl.j[u]] >= anc_d ? tl.j[u] : tl.p[u];
    return u;
};
