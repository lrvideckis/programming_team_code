#define _USE_MATH_DEFINES//M_PI
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
typedef long long ll;
typedef long double ld;

ll power(ll a, ll b, ll &c) {//returns a^b mod c
    if (b <= 0) return 1;
    ll temp = power(a, b / 2, c) % c;
    if (b % 2 == 0) {
        return (temp * temp) % c;
    }
    else {
        return (((a * temp) % c) * temp) % c;
    }
}

int main() {
    return 0;
}















