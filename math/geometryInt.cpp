#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

vector<pair<int, int>> getHull(vector<pair<int, int> > &poly) {
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

double linePointDist(pair<int, int> p1, pair<int, int> p2, pair<int, int> p) {
    if(p1.first == p2.first && p1.second == p2.second) {
        if(p.first == p1.first && p.second == p1.second) return 0;
        return sqrt(dist(p, p1));
    }
    return abs(ccw(p1, p2, p) / sqrt(dist(p1, p2)));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
	vector<pair<int, int> > poly(n);
	for(int i = 0; i < n; i++) {
	    cin >> poly[i].first >> poly[i].second;
	}
	poly = getHull(poly);
    n = poly.size();
    return 0;
}














