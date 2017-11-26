#define _USE_MATH_DEFINES//M_PI
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
typedef long long ll;
typedef long double ld;

bool isPrime(ll num) {
    if (num == 2) return true;
    if (num <= 1 || !(num % 2)) return false;
    ll root = (ll)sqrtl(num);
    for (ll i = 3; i <= root; i += 2) if (!(num%i)) return false;
    return true;
}


struct factor {
    ll value, power;
};

vector<factor> getFactors(ll number, vector<bool> &prime) {
    vector<factor> factors;
    ll root = (ll)sqrt(number), tempNum = number;
    for (ll i = 2; i <= root; i++) {
        if (!(tempNum % i) && prime[i]) {//if we find a new prime factor
            if (factors.size()) {//if its not empty
                if (factors[factors.size() - 1].value == i) {//if its the same value
                    factors[factors.size() - 1].power++;//increment the power
                }
                else {//otherwise
                    factor temp;
                    temp.value = i;
                    temp.power = 1;
                    factors.push_back(temp);//pushback the value and power
                }
            }
            else {//if it is empty pushback the value and power
                factor temp;
                temp.value = i;
                temp.power = 1;
                factors.push_back(temp);
            }
            tempNum /= i;
            i--;
        }
    }
    if (tempNum != 1) {
        factor temp;
        temp.value = tempNum;
        temp.power = 1;
        factors.push_back(temp);
    }
    /*end of extracting factors*/
    return factors;
}

int main() {
    const ll upper = 46350;//sqrt(2^31 - 1)
    ll rot = (ll)sqrt(upper + 1);
    vector<bool> isPrime(upper + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (ll i = 4; i <= upper; i += 2) isPrime[i] = false;
    for (ll i = 3; i <= rot; i += 2) {
        if (isPrime[i]) {
            for (int j = 2 * i; j <= upper; j += i) isPrime[j] = false;
        }
    }
    //example usage
    vector<factor> factors = getFactors(72, isPrime);
    for(int i = 0; i < factors.size(); i++) {
        cout << factors[i].value << '^' << factors[i].power << ' ';
    }
    cout << endl;
    return 0;
}
