#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"

#include "../../../library/strings/suffix_array_related/suffix_array.hpp"

#include "../../../library/strings/suffix_array_related/suf_cmp.hpp"
#include "../../../library/strings/suffix_array_related/substr_cmp.hpp"

#include "../../../library/strings/suffix_array_related/find_str.hpp"

#include "../../../library/strings/suffix_array_related/lcp_array.hpp"

#include "../../../library/strings/suffix_array_related/lcp_query.hpp"
#include "../../../library/strings/suffix_array_related/find_substrs_concatenated.hpp"

#include "../../../library/strings/suffix_array_related/lcp_interval_tree/find_str.hpp"

#include "../../../library/strings/knuth_morris_pratt.hpp"

#include "../../../library/strings/manacher/longest_from_index.hpp"
#include "../../../library/strings/manacher/count_palindromes_query.hpp"
#include "../../../library/strings/manacher/longest_palindrome_query.hpp"

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
            assert(suf_cmp(sa_inv, i - 1, i) < 0);
        for (int i = 0; i < 100; i++) {
            assert(suf_cmp(sa_inv, 100, i) < 0);
            assert(suf_cmp(sa_inv, i, 100) > 0);
            assert(suf_cmp(sa_inv, i, i) == 0);
        }
        assert(suf_cmp(sa_inv, 100, 100) == 0);
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
        vector<int> lcp = get_lcp_array({sa, sa_inv}, arr);
        for (int val : lcp) assert(val == 0);
    }
    {
        lcp_query lq(arr, SHIFT + 100);
        assert(lq.get_lcp(0, 99) == 0);
        assert(lq.get_lcp(0, 100) == 0);
        for (int i = 0; i < 100; i++) {
            auto [le, ri] = find_substrs_concated(lq, {{i, i + 1}});
            assert(le == i && ri == i + 1);
        }
        auto [le, ri] = find_substrs_concated(lq, {});
        assert(le == 0 && ri == ssize(arr));
        assert(substr_cmp(lq, 0, 0, 100, 100) == 0);
        assert(substr_cmp(lq, 5, 5, 47, 47) == 0);
        assert(substr_cmp(lq, 50, 50, 99, 100) < 0);
        assert(substr_cmp(lq, 50, 51, 20, 20) > 0);
        assert(substr_cmp(lq, 0, 100, 0, 100) == 0);
        assert(substr_cmp(lq, 1, 100, 0, 100) > 0);
        assert(substr_cmp(lq, 0, 100, 1, 100) < 0);
    }
    {
        lcp_tree lt(arr, SHIFT + 100);
        auto [le, ri] = find_str(lt, t);
        assert(le == 50 && ri == 51);
    }
    {
        KMP kmp(t);
        vector<int> matches = kmp.find_str(arr);
        assert(matches == vector<int>({50}));
    }
    {
        vector<int> man(manacher(arr)), longest(longest_from_index(man));
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
        count_pal_query cpq(arr);
        longest_pal_query lpq(arr);
        for (int le = 0; le < 100; le++) {
            for (int ri = le + 1; ri <= 100; ri++) {
                assert(cpq.count_pals(le, ri) == ri - le);
                auto [idx, len] = lpq.longest_pal(le, ri);
                assert(le <= idx && idx < ri);
                assert(len == 1);
            }
        }
    }
    cout << "Hello World\n";
    return 0;
}
