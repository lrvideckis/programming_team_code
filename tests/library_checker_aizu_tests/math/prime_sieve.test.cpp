#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_C"
#include "../template.hpp"

#include "../../../library/math/prime_sieve.hpp"

#include "../kactl_macros.hpp"
#include "../../../kactl/content/number-theory/MillerRabin.h"

int main() {
    init_sieve();
    for (int i = 1; i < N; i++)
        assert(isPrime(i) == is_prime(i));
    int n;
    cin >> n;
    map<int, int> prime_to_max_exponent;
    while (n--) {
        int val;
        cin >> val;
        map<int, int> curr;
        {
            int prev_prime = -1;
            for (int prime_factor : get_prime_factors(val)) {
                assert(prime_factor >= prev_prime);
                prev_prime = prime_factor;
                curr[prime_factor]++;
            }
        }
        for (auto [p, e] : curr)
            prime_to_max_exponent[p] = max(prime_to_max_exponent[p], e);
    }
    int res = 1;
    for (auto [p, e] : prime_to_max_exponent) {
        while (e--)
            res *= p;
    }
    cout << res << '\n';
    return 0;
}
