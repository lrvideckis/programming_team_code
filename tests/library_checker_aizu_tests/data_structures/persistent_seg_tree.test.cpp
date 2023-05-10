#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"
#include "../template.hpp"

#include "../../../library/data_structures/uncommon_data_structures/persistent_segment_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<array<int, 3>> points(n);
    vector<int> all_y(n);
    for(int i = 0; i < n; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        points[i] = {x, y, w};
        all_y[i] = y;
    }

    sort(begin(points), end(points));

    sort(begin(all_y), end(all_y));
    all_y.erase(unique(begin(all_y), end(all_y)), end(all_y));

    PST pst(-5, ssize(all_y));

    for(auto& point : points) {
        point[1] = int(lower_bound(begin(all_y), end(all_y), point[1]) - begin(all_y));
        pst.update(point[1], point[2], ssize(pst.roots) - 1);
    }

    while(q--) {
        int le, down, ri, up;
        cin >> le >> down >> ri >> up;
        le = int(lower_bound(begin(points), end(points), array<int, 3>({le, -1, -1})) - begin(points));
        ri = int(lower_bound(begin(points), end(points), array<int, 3>({ri, -1, -1})) - begin(points));

        down = int(lower_bound(begin(all_y), end(all_y), down) - begin(all_y));
        up = int(lower_bound(begin(all_y), end(all_y), up) - begin(all_y));
        cout << pst.query(down, up, ri) - pst.query(down, up, le) << '\n';
    }

    return 0;
}
