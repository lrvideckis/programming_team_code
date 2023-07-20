#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"

#include "../../../library/strings/suffix_array_related/suffix_array.hpp"

#include "../../../library/strings/suffix_array_related/suf_cmp.hpp"

#include "../../../library/strings/suffix_array_related/find_str.hpp"
#include "../../../library/strings/suffix_array_related/find_first.hpp"

#include "../../../library/strings/suffix_array_related/longest_common_prefix_array.hpp"

#include "../../../library/strings/suffix_array_related/lcp_query.hpp"
#include "../../../library/strings/suffix_array_related/find_substr.hpp"

#include "../../../library/strings/suffix_array_related/lcp_interval_tree.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    //mainly to test all strings algs compile when passing in vectors
    //I had a bug where `compare` is only for strings, making `find_str` useless when using vectors
    const int SHIFT = 100'000;
    vector<int> arr;
    for (int i = 0; i < 100; i++)
        arr.push_back(SHIFT + i);
    auto [sa, sa_inv] = get_sa(arr, SHIFT + 100);
    {
        for (int i = 1; i < 100; i++)
            assert(suf_cmp(sa_inv, i - 1, i));
    }
    vector<int> t;
    for (int i = 50; i < 60; i++)
        t.push_back(SHIFT + i);
    {
        auto [le, ri] = find_str(arr, sa, t);
        assert(le == 50 && ri == 51);
    }
    {
        find_first ff(arr, SHIFT + 100);
        assert(ff.first_match(t) == 50);
    }
    {
        vector<int> lcp = get_lcp_array({sa, sa_inv}, arr);
        for (int val : lcp) assert(val == 0);
    }
    {
        lcp_query lq(arr, SHIFT + 100);
        assert(lq.get_lcp(0, 99) == 0);
        for (int i = 0; i < 100; i++) {
            auto [le, ri] = find_substr(lq, i, i + 1);
            assert(le == i && ri == i + 1);
        }
    }
    {
        lcp_tree lcpt(arr, SHIFT + 100);
        auto [le, ri] = lcpt.find_str(t);
        assert(le == 50 && ri == 51);
    }
    cout << "Hello World\n";
    return 0;
}
