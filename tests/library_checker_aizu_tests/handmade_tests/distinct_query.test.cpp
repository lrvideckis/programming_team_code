#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/contest/random.hpp"

#include "../../../library/data_structures/persistent_seg_trees/distinct_query.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int tests = 10; tests--;) {
        int n = get_rand(1, 100);
        vector<int> arr(n);
        if (get_rand(0, 1) == 1)
            generate(begin(arr), end(arr), []() {return get_rand<int>(INT_MIN, INT_MAX);});
        else
            generate(begin(arr), end(arr), []() {return get_rand<int>(-2, 2);});
        distinct_query pst(arr);
        for (int i = 0; i <= n; i++) {
            auto curr = pst.query(i, i);
            assert(curr == 0);
        }
        for (int l = 0; l < n; l++) {
            for (int r = l; r <= n; r++) {
                set<int> copy_arr(begin(arr) + l, begin(arr) + r);
                auto curr_res = pst.query(l, r);
                assert(curr_res == ssize(copy_arr));
            }
        }
    }
    cout << "Hello World\n";
    return 0;
}
