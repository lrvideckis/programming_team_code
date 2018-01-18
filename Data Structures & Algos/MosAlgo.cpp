#define _USE_MATH_DEFINES//M_PI
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
#define endl '\n'
#define int long long
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define uni(x) (x).erase(unique(all(x)), (x).end());
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define rep1(i, n) for (int i = 1; i <= (int)(n); ++i)
const ll infll = powl(2, 62)-1;
//const int mod = powl(10, 9) + 7;

struct query {
    int l, r, i;
};

int n, root, counter = 0;
vector<int> arr;
unordered_map<int, int> table;//make this a map if TLE

inline void add(int i) {
    if(table[arr[i]] == arr[i]) {
        counter--;
        table[arr[i]]++;
        return;
    }
    table[arr[i]]++;
    if(table[arr[i]] == arr[i]) {
        counter++;
    }
}

inline void remove(int i) {
    if(table[arr[i]] == arr[i]) {
        counter--;
        table[arr[i]]--;
        return;
    }
    table[arr[i]]--;
    if(table[arr[i]] == arr[i]) counter++;
}

bool cmp(query a, query b) {
    if(a.l/root == b.l/root) return a.r < b.r;
    return a.l < b.l;
}

int32_t main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int m;
    cin >> n >> m;
    root = ceil(sqrt(n));
    arr.resize(n);
    rep(i,n) cin >> arr[i];
    vector<query> qs(m);
    vector<int> ans(m);
    rep(i,m) {
        cin >> qs[i].l >> qs[i].r;
        qs[i].l--;
        qs[i].r--;
        qs[i].i = i;
    }
    sort(all(qs), cmp);
    int left = 0, right = 0;
    add(0);
    rep(i,m) {
        int l = qs[i].l, r = qs[i].r;
        while(right < r) {
            right++;
            add(right);
        }
        while(left < l) {
            remove(left);
            left++;
        }
        while(left > l) {
            left--;
            add(left);
        }
        while(right > r) {
            remove(right);
            right--;
        }
        ans[qs[i].i] = counter;
    }
    rep(i,m) cout << ans[i] << endl;
    return 0;
}
















