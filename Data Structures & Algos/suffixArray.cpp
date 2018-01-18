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
const ll mod = powl(10, 9) + 7;

const int MAXN = 1 << 21;
string s;
int N, gap;
int sa[MAXN], pos[MAXN], lcp[MAXN], tmp[MAXN];

bool sufCmp(int i, int j) {
    if(pos[i] != pos[j]) return pos[i] < pos[j];
    i += gap;
    j += gap;
    return (i < N && j < N) ? pos[i] < pos[j] : i > j;
}

void buildSA() {
    N = s.length();
    for(int i = 0; i < N; ++i) {
        sa[i] = i;
        pos[i] = s[i];
    }
    for(gap = 1;; gap *= 2) {
        sort(sa, sa + N, sufCmp);
        for(int i = 0; i < N-1; ++i)
            tmp[i+1] = tmp[i] + sufCmp(sa[i], sa[i+1]);
        for(int i = 0; i < N; ++i) pos[sa[i]] = tmp[i];
        if(tmp[N-1] == N-1) break;
    }
}

void buildLCP() {
    N = s.size();
    for(int i = 0, k = 0; i < N; ++i) {
        if(pos[i] != 0 ) {
            for(int j = sa[pos[i]-1]; s[i+k] == s[j+k];) k++;
            lcp[pos[i]] = k;
            if(k) k--;
        }
    }
}

int32_t main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    
    return 0;
}








































