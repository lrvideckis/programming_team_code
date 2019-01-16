#include <bits/stdc++.h>
using namespace std;

const int Max = 1e6;
bitset<Max> prime;
int seive[Max], mob[Max];

//returns 0 iff there exists a prime p s.t. n%(p^2)=0
//returns -1 iff n has an odd number of distinct prime factors
//returns 1 iff n has an even number of distinct prime factors
int mobius(int n) {
    int &temp = mob[n];
    if(temp != -2) return temp;
    int factors = 0, counter = 1, prev = 0;
    while(n > 1) {
        if(prev == seive[n]) counter++;
        else counter = 1;
        if(counter == 2) {
            return temp = 0;
        }
        prev = seive[n];
        n /= seive[n];
        factors++;
    }
    if(counter == 2) {
        return temp = 0;
    }
    return temp = (factors%2==0?1:-1);
}

inline int shift(int pos) {
    if(pos%6==1) return pos/3+1;
    return (pos+1)/3;
}

void doSeive() {
    for (int i = 0; i < Max; ++i) {
        mob[i] = -2;
        seive[i] = i;
        prime[i] = true;
    }
    seive[0] = seive[1] = -1;
    for (int i = 2; i*i < Max; ++i) {
        if (seive[i] == i) {
            for (int j = 2 * i; j < Max; j += i) seive[j] = min(seive[j], i);
        }
    }
    for(int i = 6; i < Max; i += 6) {
        if(prime[shift(i-1)]) {
            for(int j = 2*(i-1); j < Max; j += (i-1)) {
                if(j%6 == 1 || j%6 == 5) {
                    prime[shift(j)] = false;
                }
            }
        }
        if(prime[shift(i+1)]) {
            for(int j = 2*(i+1); j < Max; j += (i+1)) {
                if(j%6 == 1 || j%6 == 5) {
                    prime[shift(j)] = false;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    doSeive();
    for(int i = 0; i < 20; ++i) {
        if(seive[i] == i) {
            cout << i << ' ';
        }
    }
    cout << '\n';
    for(int i = 6; i < 30; i += 6) {
        if(prime[shift(i-1)]) {
            cout << i-1 << ' ';
        }
        if(prime[shift(i+1)]) {
            cout << i+1 << ' ';
        }
    }
    cout << '\n';
    for(int i = 1; i < 20; ++i) {
        cout << mobius(i) << ' ';
    }
    cout << '\n';
    return 0;
}

















