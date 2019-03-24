ll dist(pair<int, int> a, pair<int, int> b) {
    int dx1 = b.first - a.first;
    int dy1 = b.second - a.second;
    return 1LL * dx1 * dx1 + 1LL * dy1 * dy1;
}

ll ccw(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
    int dx1 = b.first - a.first;
    int dy1 = b.second - a.second;
    int dx2 = c.first - a.first;
    int dy2 = c.second - a.second;
    return 1LL * dx1 * dy2 - 1LL * dy1 * dx2;
}

vector<pair<int, int>> getPoly(vector<pair<int, int> > &poly) {
    int n = poly.size();
    pair<int, int> least = poly[0];
    int pos = 0;
    for(int i = 0; i < n; i++) {
        if(poly[i] < least) {
            least = poly[i];
            pos = i;
        }
    }
    swap(poly[0], poly[pos]);
    sort(poly.begin() + 1, poly.end(), [&](const pair<int, int> &a, const pair<int, int> &b){
        auto x = ccw(poly[0], a, b);
        if(x != 0) return x > 0;
        return dist(poly[0], a) < dist(poly[0], b);
    });
    vector<pair<int, int> > hull;
    for(auto &i : poly) {
        while(hull.size() >= 2 && ccw(hull[hull.size()-2], hull.back(), i) <= 0){
            hull.pop_back();
        }
        hull.push_back(i);
    }
    return hull;
}
