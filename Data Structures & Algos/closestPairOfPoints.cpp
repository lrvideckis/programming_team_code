#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;

const int inf = 1e18;

int dist(const pair<int, int> &a, const pair<int, int> &b) {
    return (a.first-b.first)*(a.first-b.first) + (a.second-b.second)*(a.second-b.second);
}

bool cmpY(const pair<int, int> &a, const pair<int, int> &b) {
    return a.second < b.second;
}

int closestPair(vector<pair<int, int>> &points, int l, int r) {//inclusive
    if(r-l+1 <= 3) {
        int least = inf;
        for(int i = l; i <= r; ++i) {
            for(int j = i+1; j <= r; ++j) {
                least = min(least, dist(points[i], points[j]));
            }
        }
        return least;
    }
    int mid = (l+r)/2;
    int least = closestPair(points, l, mid);
    least = min(least, closestPair(points, mid+1, r));
    vector<pair<int, int>> strip;
    for(int i = l; i <= r; ++i) {
        int distToStrip = (points[i].first-points[mid].first)*(points[i].first-points[mid].first);
        if(distToStrip <= least) {
            strip.push_back(points[i]);
        }
    }
    sort(strip.begin(), strip.end(), cmpY);
    for(int i = 0; i < strip.size(); ++i) {
        for(int j = i+1; j < strip.size(); ++j) {
            int currDist = dist(strip[i], strip[j]);
            if(currDist > least) break;
            least = min(least, currDist);
        }
    }
    return least;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<pair<int, int>> points;
    cout << closestPair(points, 0, (int)points.size()-1) << '\n';
    return 0;
}



























