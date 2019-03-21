struct sparseTable {
    vector<vector<ll> > memo;
    vector<int> logTwo;
    int maxPow;
    sparseTable(const vector<ll> &arr) {
        int n = arr.size();
        logTwo.resize(n+1,0);
        for(int i = 2; i <= n; ++i) logTwo[i] = 1 + logTwo[i/2];
        maxPow = logTwo[n]+1;
        memo.resize(maxPow, vector<ll>(n));
        for(int j = 0; j < maxPow; ++j) {
            for(int i = 0; i < n; ++i) {
                if(i+(1<<j)-1<n) {
                    memo[j][i] = (j?min(memo[j-1][i], memo[j-1][i+(1<<(j-1))]):arr[i]);
                } else break;
            }
        }
    }
    ll query(int l, int r) {
        int j = logTwo[r-l+1];
        return min(memo[j][l], memo[j][r-(1<<j)+1]);
    }
};
