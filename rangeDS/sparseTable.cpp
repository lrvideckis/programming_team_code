template <class T>
struct sparseTable {
	vector<int> log2;
	vector<vector<T>> dp;
	vector<vector<int>> index;
	sparseTable(const vector<T> &arr) {
		const int n = arr.size();
		log2.resize(n+1,-1);
		for(int i = 1; i <= n; ++i) log2[i] = 1 + log2[i/2];
		const int maxPow = log2[n]+1;
		dp.resize(maxPow, vector<T>(n));
		index.resize(maxPow, vector<int>(n));
		for(int j = 0; j < n; ++j) {
			dp[0][j] = arr[j];
			index[0][j] = j;
		}
		for(int i = 1; i < maxPow; ++i) {
			for(int j = 0; j+(1<<i)-1<n; ++j) {
				if(dp[i-1][j] > dp[i-1][j+(1<<(i-1))]) {
					dp[i][j] = dp[i-1][j+(1<<(i-1))];
					index[i][j] = index[i-1][j+(1<<(i-1))];
				} else {
					dp[i][j] = dp[i-1][j];
					index[i][j] = index[i-1][j];
				}
			}
		}
	}
	int query(int l, int r) {//returns index in array of min element
		const int x = log2[r-l+1];
		if(dp[x][l] > dp[x][r-(1<<x)+1]) {
			return index[x][r-(1<<x)+1];
		}
		return index[x][l];
	}
};
