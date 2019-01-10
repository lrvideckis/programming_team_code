#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

///////////////////////////////////////////////////////////////////////////
// code credit : https://github.com/niklasb/contest-algos/
// blob/master/convex_hull/dynamic.cpp
const ll is_query = -(1LL<<62);
struct Line {
    ll m, b;
    mutable function<const Line*()> succ;
    bool operator<(const Line& rhs) const {
        if (rhs.b != is_query) return m < rhs.m;
        const Line* s = succ();
        if (!s) return 0;
        ll x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};
struct HullDynamic : public multiset<Line> { // will maintain upper hull for maximum
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end()) return y->m == x->m && y->b <= x->b;
        return (x->b - y->b) * (long double)(z->m - y->m) >= (y->b - z->b) * (long double)(y->m - x->m);
    }
    void insert_line(ll m, ll b) {
        auto y = insert({ m, b });
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y)) { erase(y); return; }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
    }
    ll getVal(ll x) {
        auto l = *lower_bound((Line) { x, is_query });
        return l.m * x + l.b;
    }
};
///////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////
const int Max = 1e6+2;
int len, ptr;
ll M[Max], B[Max];

//must insert lines in order of non-increasing slope
void addLine(ll m, ll b) {
    while(len >= 2 && (B[len-2]-B[len-1])*(m-M[len-1]) >= (B[len-1]-b)*(M[len-1]-M[len-2])) {
        --len;
    }
    M[len] = m;
    B[len] = b;
    ++len;
}

//query in order of non-decreasing x-value
ll minValue(ll x) {
    ptr = min(ptr, len-1);
    while(ptr + 1 < len && M[ptr+1]*x + B[ptr+1] <= M[ptr]*x + B[ptr]) {
        ++ptr;
    }
    return M[ptr]*x + B[ptr];
}
//Code modified from:
//https://sites.google.com/site/indy256/algo/convex_hull_optimization
///////////////////////////////////////////////////////////////////////////

int main() {
    ptr = len = 0;//clear stack
    
    return 0;
}




























