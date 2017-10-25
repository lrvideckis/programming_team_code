#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;

struct factor {
    ll value, power;
};

bool isPrime(ll num) {
    if (num == 2) return true;
    if (num <= 1 || !(num % 2)) return false;
    ll root = (ll)sqrt(num);
    for (ll i = 3; i <= root; i += 2) if (!(num % i)) return false;
    return true;
}

//this function takes in a number and returns the sum of all of the divisors
ll sumOfFactors(ll number) {
    /*extract factors*/
    vector<factor> factors;
    ll root = (ll)sqrt(number), tempNum = number;
    for (ll i = 2; i <= root; i++) {
        if (!(tempNum % i) && isPrime(i)) {//if we find a new prime factor
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

    ll sum = 1;
    for (ll i = 0; i < (ll)factors.size(); i++) {
        sum *= (((ll)pow(factors[i].value, factors[i].power + 1) - 1) / (factors[i].value - 1));
    }
    sum -= number;
    /*sum == number if number is a perfect number*/
    return sum;
}

int main() {
    for(int i = 0; i < 100; i++) {
        cout << i << ' ' << sumOfFactors(i) << endl;
    }
    return 0;
}
