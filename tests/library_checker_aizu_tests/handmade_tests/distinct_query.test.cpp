#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/misc/random.hpp"

#include "../../../library/data_structures/uncommon_data_structures/distinct_query.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int tests = 10; tests--;) {
        int n = get_rand(1, 100);
        vector<int> arr(n);
        if (get_rand(0, 2) == 1)
            generate(begin(arr), end(arr), []() {return get_rand<int>(INT_MIN, INT_MAX);});
        else
            generate(begin(arr), end(arr), []() {return get_rand<int>(-2, 3);});
        distinct_query pst(arr);
        for (int i = 0; i <= n; i++) assert(pst.query(i, i) == 0);
        for (int l = 0; l < n; l++) {
            for (int r = l; r <= n; r++) {
                set<int> copy_arr(begin(arr) + l, begin(arr) + r);
                assert(pst.query(l, r) == ssize(copy_arr));
            }
        }
    }
    cout << "Hello World\n";
    return 0;
}
