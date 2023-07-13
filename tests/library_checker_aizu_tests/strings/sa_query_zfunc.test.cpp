#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "../template.hpp"
#include "../../../library/misc/random.hpp"

#include "../../../library/strings/enhanced_suffix_array.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    enhanced_sa esa(s, 128);
    //test `less` function
    {
        for (int num_tests = 50; num_tests--;) {
            auto le = get_rand<int>(0, ssize(s) - 1);
            auto ri = get_rand<int>(0, ssize(s) - 1);
            if (le > ri)
                swap(le, ri);
            assert(esa.less(le, ri) == (s.substr(le) < s.substr(ri)));
        }
    }
    for (int i = 0; i < ssize(s); i++)
        cout << esa.get_lcp(i, 0) << " ";
    cout << '\n';
    return 0;
}
