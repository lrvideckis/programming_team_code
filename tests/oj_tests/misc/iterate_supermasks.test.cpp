#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_11_B"
#include "../../template.hpp"

#include "../../../library/misc/iterate_supermasks.hpp"

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k;
	cin >> n >> k;
	int mask = 0;
	for (int i = 0; i < k; i++) {
		int bit;
		cin >> bit;
		mask |= 1 << bit;
	}
	vector<int> supermasks;
	auto func = [&](int mask) {
		supermasks.push_back(mask);
	};
	iterate_supermasks(mask, n, func);
	sort(supermasks.begin(), supermasks.end());
	for (auto supermask : supermasks) {
		cout << supermask << ':';
		for (int bit = 0; bit < n; bit++) {
			if ((supermask >> bit) & 1)
				cout << ' ' << bit;
		}
		cout << '\n';
	}
	return 0;
}
