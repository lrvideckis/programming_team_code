#define PROBLEM "https://judge.yosupo.jp/problem/prefix_substring_lcs"
#include "../template.hpp"

//#include "../../../library/strings/longest_common_subsequence/lcs_queries.hpp"
#include "../../../library/strings/longest_common_subsequence/lcs_dp.hpp"
#include "../../../library/data_structures/wavelet_merge/wavelet_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q;
    string s, t;
    cin >> q >> s >> t;
    vector<vector<int>> h = lcs_dp(s, t);
    vector<wavelet_tree> wts;
    {
        lcs_dp
        for(int i = 0; i < ssize(h); i++)
            wts.emplace_back(h[i], -1, ssize(t));
    }
    vector<array<int, 3>> queries(q);
    vector<int> res_from_wavelet(q);
    for (int i = 0; i < q; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        queries[i] = {a, b, c};

        cout << (a == 0 ? 0 : wts[a-1].rect_count(b, c, -1, b)) << '\n';
        //res_from_wavelet[i] = wts[a].rect_count(b + 1, c + 1, 0, b + 1);
    }
    //vector<int> res = lcs_queries(h, queries);
    //assert(res == res_from_wavelet);
    //for (int val : res) cout << val << '\n';
    return 0;
}
