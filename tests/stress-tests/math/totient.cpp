#include "../../template.h"
#include "../test_utilities/generators/random.h"

#include "../../../Library/math/totient.h"

int main() {

	int MX = 3e5;

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

	cout << "Tests passed!" << endl;
	return 0;
}
