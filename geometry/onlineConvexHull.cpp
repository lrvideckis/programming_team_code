#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
int main() {
    ptr = len = 0;//clear stack
    
    return 0;
}




























