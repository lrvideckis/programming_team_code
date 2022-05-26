#define PROBLEM "https://judge.yosupo.jp/problem/partition_function"
#include "../../template.h"

#include "../../../Library/math/partitions.h"

int main() {

	int n;
	cin >> n;

	for(int val : partitions(n+1, 998244353)) {
		cout << val << " ";
	}

	cout << endl;

	return 0;
}
