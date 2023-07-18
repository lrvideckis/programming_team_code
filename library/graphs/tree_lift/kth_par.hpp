/** @file */
#pragma once
#include "constructor.hpp"
/**
 * @param tl tree lift
 * @param u query node
 * @param k number of edges
 * @returns a node k edges up from u. With k=1, this returns u's parent.
 * @time O(log k)
 * @space O(1)
 */
inline int kth_par(const tree_lift& tl, int u, int k) {
    if (k > tl.d[u]) return -1;
    int anc_d = tl.d[u] - k;
    while (tl.d[u] > anc_d) u = tl.d[tl.j[u]] >= anc_d ? tl.j[u] : tl.p[u];
    return u;
}
