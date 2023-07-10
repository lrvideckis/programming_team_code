#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_3_D"
//since _GLIBCXX_DEBUG causes std::map insert/erase operations to be O(n)
#undef _GLIBCXX_DEBUG
#include "../template.hpp"

#include "../../../library/data_structures/uncommon_data_structures/deque.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, l;
    cin >> n >> l;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    vector<int> init(begin(arr), begin(arr) + l);
    deq<int> dq(init, [](int x, int y) {return min(x, y);});
    cout << dq.query();
    for (int i = l; i < n; i++) {
        dq.push_back(arr[i]);
        dq.pop_front();
        cout << " " << dq.query();
    }
    cout << '\n';
    return 0;
}
