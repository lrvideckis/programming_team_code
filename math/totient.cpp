//  Euler's totient function counts the positive integers
//  up to a given integer n that are relatively prime to n.
ll phi(int n) {
 int tempN = n;
 int result = n;
	for(int i = 2; i*i <= tempN; i++) {
		if(n % i == 0) {
			while(n % i == 0) {
				n /= i;
			}
			result -= result / i;
		}
	}
	if(n > 1) result -= result / n;
	return result;
}
