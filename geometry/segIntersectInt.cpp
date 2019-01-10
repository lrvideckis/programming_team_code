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


int main() {

    int n;
    cin >> n;
    point p1, p2;
    p1.x.second = 1;
    p1.y.second = 1;
    p2.x.second = 1;
    p2.y.second = 1;
    vector<segment> arr;
    for(int i = 0; i < n; ++i) {
        cin >> p1.x.first >> p1.y.first >> p2.x.first >> p2.y.first;
        arr.push_back({p1, p2});
    }
    set<point> st;
    for(int i = 0; i < n; ++i) {
        for(int j = i+1; j < n; ++j) {
            vector<point> inter = intersect(arr[i], arr[j]);
            if(inter.size() == 2) {
                cout << "-1\n";
                return 0;
            }
            if(inter.size() == 1) {
                st.insert(inter[0]);
            }
        }
    }
    cout << st.size() << '\n';
    return 0;
}
















