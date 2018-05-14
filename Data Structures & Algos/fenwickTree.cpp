#include <bits/stdc++.h>
using namespace std;

struct fenwickTree {
    vector<int> bit;
    int n;
    void init(int n) {
        this->n = n;
        bit.assign(n,0);
    }
    int sum(int r) {
        int ret = 0;
        for(; r >= 0; r = (r&(r+1))-1)
            ret += bit[r];
        return ret;
    }
    void add(int idx, int d) {
        for(; idx < n; idx = idx | (idx+1)) 
            bit[idx] += d;
    }
    int sum(int l, int r) {
        return sum(r) - sum(l-1);
    }
    void init(vector<int> a) {
        init(a.size());
        for(size_t i = 0; i < a.size(); ++i)
            add(i,a[i]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    return 0;
}


























