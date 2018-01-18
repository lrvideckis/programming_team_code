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

#define INF (int)(pow(2,31)-1)
#define SQR(a) ((a)*(a))
#define COLINEAR 0
#define CW 1
#define CCW 2
struct point {
    ld x, y;
    point(ld xloc, ld yloc) : x(xloc), y(yloc) {}
    point(){}
    point& operator= (const point& other) {
        x = other.x, y = other.y;
        return *this;
    }
    int operator == (const point& other) const {
        return (other.x == x && other.y == y);
    }
    int operator != (const point& other) const {
        return !(other.x == x && other.y == y);
    }
    bool operator< (const point& other) const {
        return (x<other.x?true:(x==other.x && y < other.y));
    }
};
struct vect{ld i, j;};
struct segment {
    point p1, p2;
    segment(point a, point b) : p1(a), p2(b) {}
    segment(){}
};
ld crossProduct(point A, point B, point C) {
    vect AB, AC;
    AB.i = B.x - A.x;
    AB.j = B.y - A.y;
    AC.i = C.x - A.x;
    AC.j = C.y - A.y;
    return (AB.i*AC.j - AB.j*AC.i);
}
ld dotProduct(point A, point B, point C) {
    vect AB, BC;
    AB.i = B.x - A.x;
    AB.j = B.y - A.y;
    BC.i = C.x - B.x;
    BC.j = C.y - B.y;
    return (AB.i*BC.i + AB.j * BC.j);
}

int orientation(point p, point q, point r) {
    int val = (int)crossProduct(p, q, r);
    if(val == 0) return COLINEAR;
    return (val > 0) ? CW : CCW;
}

bool onSegment(point p, segment s) {
    return (p.x <= max(s.p1.x, s.p2.x) && p.x >= min(s.p1.x, s.p2.x) &&
            p.y <= max(s.p1.y, s.p2.y) && p.y >= min(s.p1.y, s.p2.y));
}

ld pointSquaredDist(point A, point B) {
    return SQR(A.x - B.x) + SQR(A.y - B.y);
}

ld pointDist(point A, point B) {
    return sqrtl(SQR(A.x - B.x) + SQR(A.y - B.y));
}

bool straddle(segment s1, segment s2) {
    ld cross1 = crossProduct(s1.p1, s1.p2, s2.p1);
    ld cross2 = crossProduct(s1.p1, s1.p2, s2.p2);
    if((cross1>0 && cross2>0) || (cross1 < 0 && cross2 < 0)) return false;
    if(cross1==0 && cross2==0 && orientation(s1.p2, s2.p1, s2.p2) != COLINEAR) return false;
    return true;
}

vector<point> intersect(segment s1, segment s2) {
    vector<point> res;
    point a = s1.p1, b = s1.p2, c = s2.p1, d = s2.p2;
    if(orientation(a,b,c) == 0 && orientation(a,b,d) == 0 &&
        orientation(c,d,a) == 0 && orientation(c,d,b) == 0) {
        point min_s1 = min(a,b), max_s1 = max(a,b);
        point min_s2 = min(c,d), max_s2 = max(c,d);
        if(min_s1 < min_s2) {
            if(max_s1 < min_s2) return res;//return false;
        }
        else if(min_s2 < min_s1 && max_s2 < min_s1) return res;//return false;
        point start = max(min_s1, min_s2), end = min(max_s1, max_s2);
        if(start==end) res.pb(start);//overlap is one point
        else {
            res.pb(min(start, end));
            res.pb(max(start, end));
        }
        return res;//return true; //remove overlap code block
    }
    double x1 = (b.x-a.x), y1 = (b.y-a.y), x2 = (d.x - c.x), y2 = (d.y - c.y);
    double u1 = (-y1*(a.x - c.x) + x1 * (a.y - c.y))/(-x2 * y1 + x1 * y2);
    double u2 = (x2 * (a.y - c.y) - y2 * (a.x - c.x)) / (-x2 * y1 + x1 * y2);
    if(u1 >= 0 && u1 <= 1 && u2 >= 0 && u2 <= 1)
        res.pb(point((a.x + u2*x1),(a.y+u2*y1))); //return true;
    return res;//return false;
}

void doTest() {
    ld a, b, c, d;
    cin >> a >> b >> c >> d;
    segment s1(point(a, b), point(c, d));
    cin >> a >> b >> c >> d;
    segment s2(point(a, b), point(c, d));
    vector<point> temp = intersect(s1, s2);
    switch(temp.size()) {
    case 0:
        cout << "none\n";
        break;
    case 1:
        cout << setprecision(2) << fixed << temp[0].x << ' ' << temp[0].y << endl;
        break;
    case 2:
        rep(i,2) {
            cout << setprecision(2) << fixed << temp[i].x << ' ' << temp[i].y << ' ';
        }
        cout << endl;
        break;
    }
}

int32_t main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int t;
    cin >> t;
    while(t--) doTest();
    return 0;
}






















