#define _USE_MATH_DEFINES//M_PI
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
typedef long long ll;
typedef long double ld;

ll choose(ll n, ll k, unordered_map<string, ll> &table) {
    if(k == 0 || k == n) {
        return 1;
    }
    string index = to_string(n)+'$'+to_string(k);
    if(table.find(index) != table.end()) return table[index];
    table[index] = choose(n-1, k-1, table)+choose(n-1, k, table);
    return table[index];
}

int main() {
    
    return 0;
}

