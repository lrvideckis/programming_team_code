#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_5_E"
#include "../../template.h"

#include "../../../library/math/n_choose_k_mod.h"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	n_choose_k nk(1001, 1e9 + 7);
	int n, k;
	cin >> n >> k;
	cout << nk.choose(k, n) << '\n';
	return 0;
}
