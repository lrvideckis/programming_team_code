#define PROBLEM "https://judge.yosupo.jp/problem/montmort_number_mod"
#include "../template.hpp"

#include "../../../library/math/derangements.hpp"

int main() {
	int n, mod;
	cin >> n >> mod;
	vector<int> der = derangements(n + 1, mod);
	for (int i = 1; i <= n; i++)
		cout << der[i] << " ";
	cout << endl;
	return 0;
}
