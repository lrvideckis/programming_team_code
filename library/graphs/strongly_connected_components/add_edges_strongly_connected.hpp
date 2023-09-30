vector<pair<int, int>> extra_edges(const vector<vector<int>>& adj, int num_sccs, const vector<int>& scc_id) {
    int n = ssize(adj);
    vector<int> to_a_node(num_sccs);
    for(int i = 0; i < n; i++) {
        to_a_node[scc_id[i]] = i;
    }
    vector<pair<int, int>> res_edges;

    if(num_sccs == 1) {
        return res_edges;
    }

    vector<vector<int>> scc_adj(num_sccs);
    vector<int> in(num_sccs), out(num_sccs);
    for(int i = 0; i < n; i++) {
        for(int v : adj[i]) {
            if(scc_id[i] == scc_id[v]) continue;
            scc_adj[scc_id[i]].push_back(scc_id[v]);
            out[scc_id[i]]++;
            in[scc_id[v]]++;
        }
    }

    vector<int> lone_nodes;
    int num_zero_in = 0, num_zero_out = 0;
    int random_zero_in = -1, random_zero_out = -1;
    for(int i = 0; i < num_sccs; i++) {
        if(in[i] == 0 && out[i] == 0) {
            lone_nodes.push_back(i);
            continue;
        }
        if(in[i] == 0) {
            num_zero_in++;
            random_zero_in = i;
        }
        if(out[i] == 0) {
            num_zero_out++;
            random_zero_out = i;
        }
    }

    assert((random_zero_in == -1) == (random_zero_out == -1));
    if(random_zero_in == -1 && random_zero_out == -1) {
        //one big cycle
        assert(n >= 2);
        for(int i = 0; i < n-1; i++) {
            res_edges.emplace_back(i, i + 1);
        }
        res_edges.emplace_back(n-1, 0);
        return res_edges;
    }

    int first_zero_out;
    vector<bool> vis(num_sccs);
    auto dfs = [&](auto&& self, int u) -> void {
        if(out[u] == 0) {
            first_zero_out = u;
        }
        for(int v : scc_adj[u]) {
            if(!vis[v]) {
                vis[v] = 1;
                self(self, v);
                //important: break out the moment we find the first zero out degree
                //WA if this isn't here, reason: complicated
                if(first_zero_out != -1) return;
            }
        }
    };
    vector<pair<int/*source*/, int/*sink*/>> blocking_matching;
    vector<bool> node_used(num_sccs);
    for(int i = 0; i < num_sccs; i++) {
        if(in[i] == 0 && out[i] == 0) continue;
        if(in[i] == 0) {
            if(!vis[i]) {
                vis[i] = 1;
                first_zero_out = -1;
                dfs(dfs, i);
                if(first_zero_out != -1) {
                    blocking_matching.emplace_back(i, first_zero_out);
                    node_used[i] = 1;
                    node_used[first_zero_out] = 1;
                }
            }
        }
    }


    /*
       cout << "size of blocking matching: " << ssize(blocking_matching) << endl;
       cout << "blocking matching: " << endl;
       for(auto [u,v] : blocking_matching) {
       cout << to_a_node[u]+1 << " " << to_a_node[v]+1 << endl;
       }
       */
    if(ssize(blocking_matching) == 1) {
        res_edges.emplace_back(blocking_matching[0].second, blocking_matching[0].first);
    } else if(ssize(blocking_matching) >= 2) {
        for(int i = 1; i < ssize(blocking_matching); i++) {
            res_edges.emplace_back(blocking_matching[i].second, blocking_matching[i-1].first);
        }
        res_edges.emplace_back(blocking_matching[0].second, blocking_matching.back().first);
    }

    queue<int> in_unused, out_unused;
    for(int i = 0; i < num_sccs; i++) {
        if(in[i] == 0 && out[i] != 0 && !node_used[i]) in_unused.push(i);
        if(out[i] == 0 && in[i] != 0 && !node_used[i]) out_unused.push(i);
    }
    while(!in_unused.empty() && !out_unused.empty()) {
        res_edges.emplace_back(out_unused.front(), in_unused.front());
        in_unused.pop();
        out_unused.pop();
    }
    while(!in_unused.empty()) {
        res_edges.emplace_back(random_zero_out, in_unused.front());
        in_unused.pop();
    }
    while(!out_unused.empty()) {
        res_edges.emplace_back(out_unused.front(), random_zero_in);
        out_unused.pop();
    }

    if(!lone_nodes.empty()) {
        assert(!res_edges.empty());
        auto [last_u, last_v] = res_edges.back();
        res_edges.pop_back();

        res_edges.emplace_back(last_u, lone_nodes[0]);
        for(int i = 1; i < ssize(lone_nodes); i++) {
            res_edges.emplace_back(lone_nodes[i-1], lone_nodes[i]);
        }
        res_edges.emplace_back(lone_nodes.back(), last_v);
    }

    for(auto& [u,v] : res_edges) {
        u = to_a_node[u];
        v = to_a_node[v];
    }
    return res_edges;
}
