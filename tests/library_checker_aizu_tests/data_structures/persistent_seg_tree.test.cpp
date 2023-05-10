#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"
#include "../template.hpp"

#include "../../../library/data_structures/uncommon_data_structures/persistent_segment_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;

    vector<array<int, 3>> points(n);
    for(int i = 0; i < n; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        points[i] = {x, y, w};
    }

    //TODO: check that CI catches these non-cam style iterators
    sort(points.begin(), points.end(), [](const array<int, 3>& a, const array<int, 3>& b) -> bool {
        return a[0] < b[0];
    });

    PST pst(-5, 1'000'000'000);

    for(const auto& point : points) {
        pst.update(point[1], point[2], ssize(pst.roots) - 1);
    }

    while(q--) {
        int le, down, ri, up;
        cin >> le >> down >> ri >> up;
        le = lower_bound(points.begin(), points.end(), array<int, 3>({le, -1, -1})) - points.begin();
        ri = lower_bound(points.begin(), points.end(), array<int, 3>({ri, -1, -1})) - points.begin();
        cout << pst.query(down, up, ri) - pst.query(down, up, le) << '\n';
    }

    return 0;
}
