#include <bits/stdc++.h>
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;//order_of_key, key_of_order
template<class TI>
using indexed_set = tree<TI,null_type,less<TI>,rb_tree_tag,tree_order_statistics_node_update>;
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define D(x) cout<<#x<<" -> "<<x<<'\n'
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define uni(x) (x).erase(unique(all(x)), (x).end())
#define rep(i, n) for (ll i = 0; i < (ll)(n); ++i)
#define rep1(i, n) for (ll i = 1; i <= (ll)(n); ++i)
const ld pi = 4.0*atanl(1.0);
const ll infll = (ll)(1e18) + 10;
const ll mod = powl(10, 9) + 7;

const int upper = 2*1e6;
vector<int> seive, memo;

//returns 0 iff there exists a prime p s.t. n%(p^2)=0
//returns -1 iff n has an odd number of distinct prime factors
//returns 1 iff n has an even number of distinct prime factors
int mobius(int n) {
    int &temp = memo[n];
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

void doSeive() {
    seive.resize(upper+1);
    seive[0] = seive[1] = 1;
    for (int i = 2; i <= upper; ++i) seive[i] = i;//O(n)
    int root = ceil(sqrt(upper));
    for (int i = 2; i <= root; ++i) {//O(nloglogn) ?
        if (seive[i] == i) {
            for (int j = 2 * i; j <= upper; j += i) seive[j] = min(seive[j], i);
        }
    }
}

int main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    doSeive();
    memo.resize(upper+1, -2);
    rep1(i,20) {
        cout << i << (seive[i]==i?" prime ":" not prime ") << seive[i] << '\n';
    }
    return 0;
}

















