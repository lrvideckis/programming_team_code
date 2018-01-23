#define _USE_MATH_DEFINES//M_PI
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
typedef long long ll;
typedef long double ld;

//returns x such that x*a == 1 (mod b)
//x only exists if gcd(a, b) == 1
ll modInverse(ll a, ll b){
    return 1<a ? b - modInverse(b%a,a)*b/a : 1;
}

int main() {
    for(int i = 2; i <= 10; i++) {
        for(int j = i+1; j < 100; ++j) {
            if(__gcd(i,j)==1)
            cout << i << ' ' << j << ' ' << modInverse(i,j) << '\n';
        }
    }
    return 0;
}










