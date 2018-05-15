#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = (int)1e9 + 7;

ll power(ll a, ll b, ll c = mod) {//returns a^b mod c
    if (b <= 0) return 1;
    ll temp = power(a, b / 2, c) % c;
    if (b % 2 == 0) {
        return (temp * temp) % c;
    }
    else {
        return (((a * temp) % c) * temp) % c;
    }
}

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

int main() {
    return 0;
}















