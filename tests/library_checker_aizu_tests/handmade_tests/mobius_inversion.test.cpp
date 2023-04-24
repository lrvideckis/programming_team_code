#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A"
#include "../template.hpp"
#include "../../../library/math/mobius_inversion.hpp"

#include "../kactl_macros.hpp"
#include "../../../kactl/content/number-theory/Factor.h"

int main() {
    calc_mobius();
    for (int i = 1; i < N; i++) {
        int val = i;
        map<int, int> factors;
        for (int prime_factor : factor(val))
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
