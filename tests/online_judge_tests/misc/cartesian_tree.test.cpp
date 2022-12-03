#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"
#include "../template.hpp"

#include "../../../library/misc/monotonic_stack_related/cartesian_tree.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	vector<int> par = cartesian_tree(arr);
	for (int i = 0; i < n; i++) {
		if (par[i] == -1) cout << i << " ";
		else cout << par[i] << " ";
	}
	return 0;
}
