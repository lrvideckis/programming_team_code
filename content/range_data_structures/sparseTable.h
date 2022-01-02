#pragma once

//to also get index of min element, do sparseTable<pair<ll,int>> and initialize
//second to index
template <class T>
struct sparseTable {
	vector<int> log2;
	vector<vector<T>> dp;
	sparseTable(const vector<T>& arr) {
		const int n = arr.size();
		log2.resize(n+1,-1);
		for(int i = 1; i <= n; ++i) log2[i] = 1 + log2[i/2];
		dp.resize(log2[n]+1, arr);
		for(int i = 1; i <= log2[n]; ++i) {
			for(int j = 0; j+(1<<i)-1<n; ++j) {
				dp[i][j] = min(dp[i-1][j], dp[i-1][j+(1<<(i-1))]);
			}
		}
	}
	//returns min of arr[l], arr[l+1], ..., arr[r]
	T query(int l, int r) const {
		const int x = log2[r-l+1];
		return min(dp[x][l], dp[x][r-(1<<x)+1]);
	}
};
