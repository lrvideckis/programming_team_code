#include "../../template.h"
#include "../../../Library/misc/random.h"

#include "../../../Library/math/totient.h"

int main() {

	for(int i = 1; i <= 800; i++) {
		int cnt = 0;
		for(int j = 1; j <= i; j++) {
			if(__gcd(i,j) == 1) cnt++;
		}
		assert(totient(i) == cnt);
	}

	cout << "Tests passed!" << endl;
	return 0;
}
