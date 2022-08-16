#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_1_C"
#include "../../template.h"

#include "../../../library/math/prime_sieve.h"

int main() {
	calc_seive();

	int n;
	cin >> n;
	int cnt_prime = 0;
	while(n--) {
		int val;
		cin >> val;
		cnt_prime += a_prime[val] == val;
	}
	cout << cnt_prime << '\n';

	return 0;
}
