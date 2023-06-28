#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/misc/random.hpp"

#include "../../../library/data_structures/uncommon_data_structures/wavelet_tree_updates.hpp"

int main() {
    for (int n = 0; n <= 200; n++) {
        for (int tests = 5; tests--;) {
            int minn = get_rand<int>(-100, 100);
            int maxn = get_rand<int>(-100, 100);
            if (minn > maxn) swap(minn, maxn);
            //values in range [minn, maxn]
            vector<int> arr(n);
            generate(begin(arr), end(arr), [&]() {return get_rand<int>(minn, maxn);});
            wavelet_tree_updates wtu(arr, minn, maxn + 1);
            vector<bool> is_active(n, 1);
            for (int operations = 50; operations--;) {
                if (operations % 3 == 0) { //rect_count query
                    int le = get_rand<int>(0, n);
                    int ri = get_rand<int>(0, n);
                    if (le > ri) swap(le, ri);
                    int x = get_rand<int>(-100, 100);
                    int y = get_rand<int>(-100, 100);
                    if (x > y) swap(x, y);
                    int count_naive = 0;
                    for (int i = le; i < ri; i++)
                        count_naive += (is_active[i] && x <= arr[i] && arr[i] < y);
                    assert(wtu.rect_count(le, ri, x, y) == count_naive);
                } else if (operations % 3 == 1) { //kth_smallest query
                    int le = get_rand<int>(0, n);
                    int ri = get_rand<int>(0, n);
                    if (le > ri) swap(le, ri);
                    vector<int> sorted;
                    for (int i = le; i < ri; i++)
                        if (is_active[i]) sorted.push_back(arr[i]);
                    sort(begin(sorted), end(sorted));
                    for (int k = 1; k <= ssize(sorted); k++)
                        assert(wtu.kth_smallest(le, ri, k) == sorted[k - 1]);
                } else {//update active status
                    assert(operations % 3 == 2);
                    if (n == 0) continue;
                    int i = get_rand<int>(0, n - 1);
                    bool new_val = get_rand<int>(0, 1);
                    wtu.set_active(i, new_val);
                    is_active[i] = new_val;
                }
            }
        }
    }
    cout << "Hello World\n";
    return 0;
}
