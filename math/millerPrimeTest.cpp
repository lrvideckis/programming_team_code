// C++ program Miller-Rabin primality test
#include <bits/stdc++.h>
#define int long long
#define ll long long
using namespace std;


ll mulmod(ll a, ll b, ll mod)
{
    ll x = 0,y = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {    
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}
/* 
 * modular exponentiation
 */
ll modulo(ll base, ll exponent, ll mod)
{
    ll x = 1;
    ll y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}
 
/*
 * Miller-Rabin primality test, iteration signifies the accuracy
 */
bool Miller(ll p,int iteration)
{
    if (p < 2)
    {
        return false;
    }
    if (p != 2 && p % 2==0)
    {
        return false;
    }
    ll s = p - 1;
    while (s % 2 == 0)
    {
        s /= 2;
    }
    for (int i = 0; i < iteration; i++)
    {
        ll a = rand() % (p - 1) + 1, temp = s;
        ll mod = modulo(a, temp, p) % mod;
        while (temp != p - 1 && mod != 1 && mod != p - 1)
        {
            mod = mulmod(mod, mod, p) % mod;
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0)
        {
            return false;
        }
    }
    return true;
}

bool isPrime2(ll num) {
    if (num == 2) return true;
    if (num <= 1 || !(num % 2)) return false;
    ll root = (ll)sqrtl(num);
    for (ll i = 3; i <= root; i += 2) if (!(num%i)) return false;
    return true;
}


// Driver program
int32_t main()
{
    int k = 50;  // Number of iterations

    for (int n = (int)1e12; n < (int)1e12+1000; n++) {
       if (Miller(n, k) != isPrime2(n))
          cout << n << " disagreement\n";

    }

    return 0;
}

























