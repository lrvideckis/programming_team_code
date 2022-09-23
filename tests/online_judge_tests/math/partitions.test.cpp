#define PROBLEM "https://judge.yosupo.jp/problem/partition_function"
#include "../template.hpp"

#include "../../../library/math/partitions.hpp"

int main() {
	int n;
	cin >> n;
	for (long long val : partitions(n + 1, 998244353))
		cout << val << " ";
	cout << endl;
	return 0;
}
