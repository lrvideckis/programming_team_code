#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
#define int long long
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define endl '\n'
#define D(x) cout<<#x<<" -> "<<x<<'\n'
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define uni(x) (x).erase(unique(all(x)), (x).end());
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define rep1(i, n) for (int i = 1; i <= (int)(n); ++i)
const ll infll = powl(2, 62)-1;
const ld pi = 4.0*atanl(1.0);
const int mod = powl(10, 9) + 7;

vector<int> p(1000001,-1);//change size here if needed
int find(int x) {return p[x] < 0 ? x : p[x] = find(p[x]);}
void merge(int x, int y) {
    if((x=find(x)) == (y=find(y))) return;
    if(p[x] < p[y]) {//set x has larger size, sizes stored as negative ints
        p[x] += p[y];
        p[y] = x;
    } else {
        p[y] += p[x];
        p[x] = y;
    }
}

int32_t main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    
    return 0;
}


























