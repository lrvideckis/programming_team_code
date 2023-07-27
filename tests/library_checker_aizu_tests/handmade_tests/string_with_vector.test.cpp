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

#include "../../../library/strings/knuth_morris_pratt.hpp"

#include "../../../library/strings/manacher/longest_from_start.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    //mainly to test all strings algs compile when passing in vectors
    //I had a bug where `compare` is only for strings, making `find_str` useless when using vectors
    const int SHIFT = 100'000;
    vector<int> arr;
    arr.reserve(100);
    for (int i = 0; i < 100; i++)
        arr.push_back(SHIFT + i);
    auto [sa, sa_inv] = get_sa(arr, SHIFT + 100);
    {
        for (int i = 1; i < 100; i++)
            assert(suf_cmp(sa_inv, i - 1, i));
    }
    vector<int> t;
    t.reserve(10);
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
    {
        KMP kmp(t);
        vector<int> matches = kmp.find_str(arr);
        assert(matches == vector<int>({50}));
    }
    {
        vector<int> man(manacher(arr)), longest(longest_from_start(man));
        for (int i = 0; i < ssize(man); i++) {
            int sz = i - 2 * man[i] + 1;
            assert(sz == (1 ^ (i & 1)));
        }
        for (int i = 0; i < 100; i++) {
            assert(longest[i] == 1);
            assert(is_pal(man, i, i + 1));
            if (i + 2 <= 100) {
                assert(!is_pal(man, i, i + 2));
                if (i)
                    assert(!is_pal(man, i - 1, i + 2));
            }
        }
    }
    cout << "Hello World\n";
    return 0;
}
