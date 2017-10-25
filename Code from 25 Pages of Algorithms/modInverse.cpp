#define _USE_MATH_DEFINES//M_PI
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
typedef long long ll;
typedef long double ld;

//returns x such that x*a == 1 (mod b)
//x only exists if gcd(a, b) == 1
ll modInverse(ll a, ll b) {
    if(b == 1) return 1;
    ll b0 = b, x0 = 0, x1 = 1, q, temp;
    while(a > 1) {
        q = a/b;
        temp = a;
        a = b;
        b = temp % b;
        temp = x0;
        x0 = x1 - q* x0;
        x1 = temp;
    }
    if(x1 < 0) x1 += b0;
    return x1;
}

int main() {
    
    return 0;
}










