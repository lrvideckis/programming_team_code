
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <limits>
#include <stack>
#include <random>

using namespace std;

typedef long long ll;

//Constant values to be returned
constexpr int Colinear = -1, NoIntersect = 0, Intersect = 1;
constexpr int CW = 2, CCW = 3;
constexpr int Inside = 4, Outside = 5, OnEdge = 6;

void sterilize(pair<ll, ll> &x) {
    if(x.first == 0) {
        x.second = 1;
        return;
    }
    int div = __gcd(x.first, x.second);
    x.first /= div;
    x.second /= div;
    if(x.second < 0) {
        x.first = -x.first;
        x.second = -x.second;
    }
}

bool operator<(pair<ll, ll> x, pair<ll, ll> y) {
    sterilize(x);
    sterilize(y);
    return x.first*y.second < y.first*x.second;
}

bool operator<=(pair<ll, ll> x, pair<ll, ll> y) {
    sterilize(x);
    sterilize(y);
    if(x == y) return true;
    return x.first*y.second < y.first*x.second;
}

bool operator>(pair<ll, ll> x, pair<ll, ll> y) {
    sterilize(x);
    sterilize(y);
    return x.first*y.second > y.first*x.second;
}

bool operator>=(pair<ll, ll> x, pair<ll, ll> y) {
    sterilize(x);
    sterilize(y);
    if(x == y) return true;
    return x.first*y.second > y.first*x.second;
}

pair<ll, ll> operator+(const pair<ll, ll> &x, const pair<ll, ll> &y) {
    pair<ll, ll> sum;
    sum.first = x.first*y.second + x.second*y.first;
    sum.second = x.second*y.second;
    sterilize(sum);
    return sum;
}

pair<ll, ll> operator-(const pair<ll, ll> &x, const pair<ll, ll> &y) {
    pair<ll, ll> sum;
    sum.first = x.first*y.second - x.second*y.first;
    sum.second = x.second*y.second;
    sterilize(sum);
    return sum;
}

pair<ll, ll> operator*(const pair<ll, ll> &x, const pair<ll, ll> &y) {
    pair<ll, ll> sum;
    sum.first = x.first*y.first;
    sum.second = x.second*y.second;
    sterilize(sum);
    return sum;
}

pair<ll, ll> operator*(const pair<ll, ll> &x, const ll &y) {
    pair<ll, ll> sum;
    sum.first = x.first*y;
    sum.second = x.second;
    sterilize(sum);
    return sum;
}

pair<ll, ll> operator/(const pair<ll, ll> &x, const ll &y) {
    pair<ll, ll> sum;
    sum.first = x.first;
    sum.second = x.second*y;
    sterilize(sum);
    return sum;
}

pair<ll, ll> operator/(const pair<ll, ll> &x, const pair<ll, ll> &y) {
    pair<ll, ll> sum;
    sum.first = x.first*y.second;
    sum.second = x.second*y.first;
    sterilize(sum);
    return sum;
}

pair<ll, ll> max(const pair<ll, ll> &x, const pair<ll, ll> &y) {
    if(x < y) return y;
    return x;
}

pair<ll, ll> min(const pair<ll, ll> &x, const pair<ll, ll> &y) {
    if(x < y) return x;
    return y;
}

struct point
{
    pair<ll, ll> x, y;

    point(ll x_, ll y_) : x({x_,1}), y({y_,1}){}
    point(pair<ll,ll> x_={0,1}, pair<ll,ll> y_={0,1}) : x(x_), y(y_) {
        sterilize(x);
        sterilize(y);
    }
    
    // Only < operator is unusual behavior
    bool operator <(const point& other) const
    {
        return (x < other.x ? true : (x == other.x && y < other.y));
    }

    bool operator == (const point& other) const
    {
        return other.x == x && other.y == y;
    }

    //Add other operators as needed
    point operator + (const point& other) const
    {
        return point(this->x + other.x, this->y + other.y);
    }

    point operator - (const point& other) const
    {
        return point(this->x - other.x, this->y - other.y);
    }

    point operator * (ll other) const
    {
        return point(this->x * other, this->y * other);
    }
    
    point operator / (ll other) const
    {
        return point(this->x / other, this->y / other);
    }
};

//Container for line segment
struct segment { point p1, p2; };

//Dot product ab.bc
pair<ll, ll> dot(const point& a, const point& b, const point& c)
{
    point AB = b - a;
    point BC = c - b;
    return AB.x*BC.x + AB.y*BC.y;
}

//Cross product
//AB X AC
pair<ll, ll> cross(const point& A, const point& B, const point& C)
{
    point AB = B - A, AC = C - A;
    return (AB.x * AC.y - AB.y * AC.x);
}

//Finds orientation of triplet of points p, q, r
//Returns Colinear, CW, or CCW
int orientation(const point& p, const point& q, const point& r)
{
    pair<ll, ll> val = cross(p, q, r);
    sterilize(val);
    if(val.first == 0) return Colinear;
    //if(val < make_pair(0,1)) return Colinear;
    return (val.first > 0) ? CW : CCW;
}

//Checks if point p is possibly on the segment s
//but doesn't guarantee it is
bool onSegment(const point& p, const segment& s)
{
    bool x = (s.p1.x == s.p2.x) && (p.x == s.p2.x) || (p.x <= max(s.p1.x, s.p2.x) && p.x >= min(s.p1.x, s.p2.x));
    bool y = (s.p1.y == s.p2.y) && (p.y == s.p2.y) || (p.y <= max(s.p1.y, s.p2.y) && p.y >= min(s.p1.y, s.p2.y));
    return x && y;
}

//Returns of list of intersection points between segments s1, and s2
//If they do not intersect, the result is an empty vector
//If they intersect at exactly 1 point, the result contains that point
//If they overlap for non-0 distance, the left and right points of that intersection
//  are returned
vector<point> intersect(const segment& s1, const segment& s2)
{

    point a = s1.p1, b = s1.p2, c = s2.p1, d = s2.p2;

    if(orientation(a, b, c) == Colinear && orientation(a, b, d) == Colinear &&
        orientation(c, d, a) == Colinear && orientation(c, d, b) == Colinear)
    {
        point min_s1 = min(a, b), max_s1 = max(a, b);
        point min_s2 = min(c, d), max_s2 = max(c, d);
        if(max_s1 < min_s2 || max_s2 < min_s1) return {};

        point start = max(min_s1, min_s2), end = min(max_s1, max_s2);
        if(start == end)
            return {start};
        else 
            return {min(start, end), max(start, end)};
    }

    pair<ll, ll> a1 = b.y - a.y, a2 = d.y - c.y;
    pair<ll, ll> b1 = a.x - b.x, b2 = c.x - d.x;
    pair<ll, ll> c1 = a1*a.x + b1*a.y, c2 = a2*c.x + b2*c.y;
    pair<ll, ll> det = a1*b2 - a2*b1;
    sterilize(det);
    if(det != make_pair(0LL,1LL))
    {
        point inter((b2*c1 - b1*c2)/det, (a1*c2 - a2*c1)/det);
        if(onSegment(inter, s1) && onSegment(inter, s2))
            return {inter};
    }
    return {};
}

//Checks if point p is inside the polygon
//Returns Inside, Outside, or OnEdge
int pointInPoly(const vector<point>& poly, const point& p)
{
    //cout << "Point in poly " << p.x << " " << p.y << endl;
    bool inside = false;

    pair<ll, ll> maxX = poly[0].x;

    for(const point& p : poly)
        maxX = max(maxX, p.x);

    //Create point definitely outside polygon
    point outside(maxX+make_pair(1,1), p.y);

    vector<point> intersection;

    for(int i=0, j = poly.size()-1; i < poly.size(); i++, j=i-1)
    { 
        if(p == poly[i] || p == poly[j]) return OnEdge;
        if(orientation(p, poly[i], poly[j]) == Colinear &&
           onSegment(p, segment{poly[i], poly[j]})) return OnEdge;

        intersection = intersect(segment{p, outside}, segment{poly[i], poly[j]});
        //cout << intersection.size() << " intersections with " << poly[i].x << ", " << poly[i].y << " -> " << poly[j].x << ", " << poly[j].y << endl;
        if(intersection.size() == 1)
        {
            if(poly[i] == intersection[0] && poly[j].y <= p.y) continue;
            if(poly[j] == intersection[0] && poly[i].y <= p.y) continue;
            //cout << intersection[0].x << " " << intersection[0].y << endl;
            inside = !inside;
        }
    }   

    //cout << "Is inside? " << inside << endl;
    return (inside ? Inside : Outside);    
}

int main() {
    int n;
    while(cin >> n && n) {
        vector<point> poly;
        int x,y;
        for(int i = 0; i < n; ++i) {
            cin >> x >> y;
            poly.push_back(point(x,y));
        }
        int m;
        cin >> m;
        while(m--) {
            cin >> x >> y;
            point curr = point(x,y);
            int res = pointInPoly(poly, curr);
            //constexpr int Inside = 4, Outside = 5, OnEdge = 6;
            if(res == OnEdge) {
                cout << "on\n";
            } else if(res == Inside) {
                cout << "in\n";
            } else {
                cout << "out\n";
            }
        }
    }
    return 0;
}





















