#include <iostream>
#include <cmath>

using namespace std;

typedef long long int ll;

ll power(ll a, ll b, int &c) {//returns a^b mod c
    if (b <= 1) return a % c;
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