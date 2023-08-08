#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"

#include "../../../library/math/n_choose_k/choose_lucas.hpp"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    calc_facts();
    for (int i = 0; i < mx_n; i++) {
        if (i) assert(i * inv[i] % mod == 1LL);
        assert(fact[i] * inv_fact[i] % mod == 1LL);
    }
    vector<vector<long long>> naive_choose(mx_n, vector<long long>(mx_n, 0));
    for (int i = 0; i < mx_n; i++) {
        naive_choose[i][0] = 1;
        for (int j = 1; j <= i; j++)
            naive_choose[i][j] = (naive_choose[i - 1][j] + naive_choose[i - 1][j - 1]) % mod;
    }
    for (int i = 0; i < mx_n; i++) {
        assert(C(1LL * i, -1LL) == 0);
        assert(C(1LL * i, 1LL * i + 1) == 0);
        assert(C(-1LL, 1LL * i) == 0);
        assert(C(1LL * i, 1LL * i - 1) == i % mod);
        for (int j = 0; j < mx_n; j++)
            assert(C(1LL * i, 1LL * j) == naive_choose[i][j]);
    }
    assert(C(371283LL, 32981LL) == 0);
    assert(C(47382946300290018LL, 47382946300290014LL) == 7);
    assert(C(4032010405302301LL, 403201040302301LL) == 0);
    assert(C(4032010405302301LL, 4032010405302298LL) == 4);
    cout << "Hello World\n";
    return 0;
}
