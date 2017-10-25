#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct partitionFunction
{
    map<ll, ll> remember;
    
    
    //The number of ways you can add to a number
    ll getPartitionsModM(ll n, ll m)
    {
        if(n < 0)
            return 0;
        if(n == 0)
            return 1;
        if(remember.find(n) != remember.end())
            return remember[n];
        ll sum = 0;
        ll val = 1;
        for(ll i = 1;  val <= n; i++)
        {
            ll multiply = 1;
            if(i % 2 == 0)
                multiply = -1;
            ll three = 3;
            val = ((three*i*i) + i) / 2;
            sum += getPartitionsModM(n - val, m) * multiply;
            val = ((three*i*i) - i) / 2;
            sum += getPartitionsModM(n - val, m) * multiply;
        }
        remember[n] = sum % m;
        return sum % m;
    }
};

int main() {
    partitionFunction p;
    cout << p.getPartitionsModM(4ll,1000ll) << '\n';
}













