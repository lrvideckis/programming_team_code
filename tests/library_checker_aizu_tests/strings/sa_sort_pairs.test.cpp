#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_5_A"
#include "../template.hpp"

#include "../../../library/strings/suffix_array_related/compare/compare_substrings.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> arr(2 * n);
    for (int& x : arr) cin >> x;
    vector<int> compress(arr);
    sort(begin(compress), end(compress));
    compress.erase(unique(begin(compress), end(compress)), end(compress));
    for (int& x : arr) {
        int le = -1, ri = int(ssize(compress));
        while (ri - le > 1) {
            int mi = le + (ri - le) / 2;
            if (compress[mi] >= x) ri = mi;
            else le = mi;
        }
        assert(0 <= ri && ri < ssize(compress) && compress[ri] == x);
        x = ri;
    }
    lcp_query lq(arr, int(ssize(compress)));
    vector<int> idxs(n);
    iota(begin(idxs), end(idxs), 0);
    sort(begin(idxs), end(idxs), [&](int i, int j) -> bool {
        return substr_cmp(lq, 2 * i, 2 * (i + 1), 2 * j, 2 * (j + 1)) < 0;
    });
    for (int idx : idxs)
        cout << compress[arr[2 * idx]] << " " << compress[arr[2 * idx + 1]] << '\n';
    return 0;
}
