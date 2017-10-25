//this function returns base^exp in log(exp) time
ll fastpow(ll base, ll exp) {
    if(exp == 0) {
        return 1;
    }
    ll temp;
    if(exp % 2 == 0) {
        temp = fastpow(base, exp / 2);
        temp *= temp;
    } else {
        temp = fastpow(base, exp - 1) * base;
    }
    return temp;
}
