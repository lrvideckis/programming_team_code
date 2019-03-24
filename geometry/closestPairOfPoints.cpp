typedef long long ll;
pair<int, int> closestPair(vector<pair<ll, ll>> &pts) {
    int n = pts.size();
    sort(pts.begin(), pts.end());
    set<pair<pair<ll, ll>, int>> s;
    ll best_dist = 1e18;
    int j = 0;
    pair<int, int> pos;
    for (int i = 0; i < n; ++i) {
        ll d = ceil(sqrt(best_dist));
        while (pts[i].first - pts[j].first > best_dist) {
            s.erase({{pts[j].second, pts[j].first}, j});
            j += 1;
        }
        auto it1 = s.lower_bound({{pts[i].second - d, pts[i].first}, -1});
        auto it2 = s.upper_bound({{pts[i].second + d, pts[i].first}, i});
        for (auto it = it1; it != it2; ++it) {
            ll dx = pts[i].first - it->first.second;
            ll dy = pts[i].second - it->first.first;
            ll dist = dx * dx + dy * dy;
            if(best_dist > dist) {
                best_dist = dist;
                pos.first = it->second;
                pos.second = i;
            }
        } 
        s.insert({{pts[i].second, pts[i].first}, i}); 
    }
    return pos;
}
