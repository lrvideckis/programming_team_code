#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/misc/random.hpp"

#include "../../../library/data_structures/uncommon_data_structures/merge_sort_tree.hpp"
#define split split_2
#include "../../../library/data_structures/uncommon_data_structures/merge_sort_tree_updates.hpp"

int main() {
    //brute force small cases
    for (int n = 0; n <= 25; n++) {
        for (int tests = 3; tests--;) {
            int minn = get_rand<int>(-1000, 1000);
            int maxn = get_rand<int>(-1000, 1000);
            if (minn > maxn) swap(minn, maxn);
            vector<int> arr(n);
            generate(begin(arr), end(arr), [&]() {return get_rand<int>(minn, maxn);});
            merge_sort_tree mst(arr);
            merge_sort_tree_updates mstu(arr);
            for (int queries = 30; queries--;) {
                int x = get_rand<int>(-1000, 1000);
                int y = get_rand<int>(-1000, 1000);
                if (x > y) swap(x, y);
                for (int le = 0; le <= n; le++) {
                    int cnt = 0;
                    for (int ri = le; ri <= n; ri++) {
                        assert(mst.query(le, ri, x, y) == cnt);
                        assert(mstu.query(le, ri, x, y) == cnt);
                        if (ri < n && x <= arr[ri] && arr[ri] < y)
                            cnt++;
                    }
                }
            }
        }
    }
    cout << "Hello World\n";
    return 0;
}
