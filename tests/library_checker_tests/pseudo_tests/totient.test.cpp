#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "../../template.h"

#include "../../../library/math/totient.h"

int main() {

	const int MX = 3e5;

	vector<int> phi(MX);
	for(int i = 0; i < MX; i++) {
		phi[i] = i;
	}

	assert(totient(1) == 1);
	for(int i = 2; i < MX; i++) {

		if(i < 500) {
			int cnt = 0;
			for(int j = 1; j <= i; j++) {
				cnt += __gcd(i,j)==1;
			}
			assert(totient(i) == cnt);
		}

		if(phi[i] == i) {
			for(int j = i; j < MX; j += i) {
				phi[j] -= phi[j] / i;
			}
		}
		assert(phi[i] == totient(i));
	}

	int a, b;
	cin >> a >> b;
	cout << a + b << endl;
	return 0;
}
