#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/misc/random.hpp"

#include "../../../library/data_structures/uncommon_data_structures/wavelet_tree.hpp"

int main() {
    //brute force small cases
    for(int n = 0; n <= 65; n++) {
        for(int tests = 3; tests--;) {
            int minn = get_rand<int>(-1000, 1000);
            int maxn = get_rand<int>(-1000, 1000);
            if(minn > maxn) swap(minn, maxn);
            vector<int> arr(n);
            for(int& val : arr) val = get_rand<int>(minn, maxn);
            wavelet_tree wt(arr, minn, maxn + 1);
            for(int queries = 3; queries--;) {
                int x = get_rand<int>(minn, maxn + 1);
                int y = get_rand<int>(minn, maxn + 1);
                if(x > y) swap(x,y);
                for(int le = 0; le <= n; le++) {
                    int cnt = 0, sum = 0;
                    for(int ri = le; ri <= n; ri++) {
                        assert(wt.rect_count(le, ri, x, y) == cnt);
                        assert(wt.rect_sum(le, ri, x, y) == sum);
                        if(ri < n && x <= arr[ri] && arr[ri] < y) {
                            cnt++;
                            sum += arr[ri];
                        }
                    }
                }
            }
        }
    }
    //max test for overflow
    {
        const int N = 100'000, LARGE = 1'000'000'000, VAL_RANGE = 20;
        vector<int> arr(N), count_val(VAL_RANGE);
        for(int& val : arr) {
            val = get_rand<int>(LARGE, LARGE+VAL_RANGE-1);
            count_val[val-LARGE]++;
        }
        wavelet_tree wt(arr, LARGE, LARGE+VAL_RANGE);
        for(int x = LARGE; x <= LARGE+VAL_RANGE; x++) {
            int cnt = 0;
            long long sum = 0;
            for(int y = x; y <= LARGE+VAL_RANGE; y++) {
                assert(wt.rect_count(0, N, x, y) == cnt);
                assert(wt.rect_sum(0, N, x, y) == sum);
                if(y < LARGE+VAL_RANGE) {
                    cnt += count_val[y-LARGE];
                    sum += 1LL * y * count_val[y-LARGE];
                }
            }
        }
    }
    cout << "Hello World\n";
    return 0;
}
