#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool isPrime(ll num) {
    if (num == 2) return true;
    if (num <= 1 || !(num % 2)) return false;
    ll root = (ll)sqrtl(num);
    for (ll i = 3; i <= root; i += 2) if (!(num%i)) return false;
    return true;
}

vector<pair<int, int> > getPrimeFactors(ll number) {
    vector<pair<int, int> > factors;
    int root = (int)sqrtl(number);
    for(int i = 2; i <= root+1; ++i) {
        while(number%i==0) {
            number /= i;
            if(factors.size() && factors.back().first == i) factors.back().second++;
            else factors.push_back({i, 1});
        }
    }
    if(number > 1) factors.push_back({number, 1});
    return factors;
}

ll sumOfDivisors(ll number) {
    auto factors = getPrimeFactors(number);
    ll sum = 1;
    for (ll i = 0; i < (ll)factors.size(); i++) {
        sum *= (((ll)pow(factors[i].first, factors[i].second + 1) - 1) / (factors[i].first - 1));
    }
    //sum -= number;
    /*sum == number if number is a perfect number*/
    return sum;
}

const int Max = (int)1e5+3;
vector<int> allFactors[Max];

void generateFactors() {
    for(int i = 1; i < Max; ++i) {
        for(int j = i; j < Max; j += i) {
            allFactors[j].push_back(i);
        }
    }
}

int main() {
    ll num = 5040;
    vector<pair<int, int> > factors = getPrimeFactors(num);
    cout << "factors of " << num << ":\n";
    for(auto &p : factors) cout << p.first << '^' << p.second << ' ';
    cout << '\n';
    generateFactors();
    for(int i = 1; i <= 12; ++i) {
        cout << "all unique factors of " << i << ":\n";
        for(int f : allFactors[i]) cout << f << ' ';
        cout << '\n';
        cout << "sum of factors: " << sumOfDivisors(i) << "\n\n";
    }
    return 0;
}





