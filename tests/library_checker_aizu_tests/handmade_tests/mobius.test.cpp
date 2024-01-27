#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/math/mobius.hpp"

#include "../../submodules/kactl/content/number-theory/Factor.h"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    calc_mobius();
    for (int i = 1; i < mx_n; i++) {
        int val = i;
        map<ull, int> factors;
        for (auto prime_factor : factor(val))
            factors[prime_factor]++;
        {
            bool found_square = 0;
            for (auto [prime, exponent] : factors) {
                if (exponent > 1) {
                    assert(mobius[i] == 0);
                    found_square = 1;
                    break;
                }
            }
            if (found_square)
                continue;
        }
        assert(1 - 2 * (ssize(factors) % 2) == mobius[i]);
    }
    cout << "Hello World\n";
    return 0;
}
