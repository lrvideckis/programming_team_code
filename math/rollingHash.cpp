//be careful with alphabet size
//this is made for a string with only digits
struct Hash {
    const int base = 10;
    vector<int> powB;
    vector<int> prefix;
    int mod;
    Hash() {}
    Hash(const string &s, const int m) {
        mod = m;
        prefix.resize(s.size());
        powB.resize(s.size() + 3, 1);
        for(int i=1;i<powB.size();++i){
            powB[i] = (powB[i-1] * 1LL * base) % mod;
        }
        for(int i=0;i<(int)s.size();++i){
            sum = (base*1LL*sum + s[i]-'0') % mod;
            prefix[i] = sum;
        }
    }
    int get(int i, int j) {
        int res = prefix[j];
        if(i-1 >= 0) {
            res -= prefix[i-1] * 1LL * powB[j-i+1] % mod;
            if(res < 0) res += mod;
        }
        return res;
    }
};
