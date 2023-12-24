/** @file */
#pragma once
/**
 * Info about which subtrees are isomorphic
 */
struct iso_info {
    int num_distinct_subtrees; /**< number of classes (by iso.) of subtrees */
    /**
     * - 0 <= iso_id[u] < num_distinct_subtrees
     * - iso_id[u] == iso_id[v] iff subtree u is isomorphic to subtree v
     */
    vector<int> iso_id;
};
/**
 * @code{.cpp}
 *     auto [num_distinct_subtrees, iso_id] = subtree_iso(adj);
 * @endcode
 * @param adj rooted forest (rooted or unrooted)
 * @returns which subtrees are isomorphic
 * @time O(n log n)
 * @space `iso_id` and `hashes` both are O(n)
 */
iso_info subtree_iso(const vector<vector<int>>& adj) {
    vector iso_id(ssize(adj), -1);
    map<vector<int>, int> hashes;
    auto dfs = [&](auto&& self, int u, int p) -> int {
        vector<int> ch_ids;
        ch_ids.reserve(ssize(adj[u]));
        for (int v : adj[u])
            if (v != p)
                ch_ids.push_back(self(self, v, u));
        sort(begin(ch_ids), end(ch_ids));
        return iso_id[u] = hashes.try_emplace(ch_ids, ssize(hashes)).first->second;
    };
    for (int i = 0; i < ssize(adj); i++)
        if (iso_id[i] == -1)
            dfs(dfs, i, i);
    return {ssize(hashes), iso_id};
}
