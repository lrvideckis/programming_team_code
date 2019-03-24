struct Fraction {
    int a, b;
    Fraction() {
        a = 0;
        b = 1;
    }
    Fraction(int _a, int _b) {
        a = _a;
        b = _b;
        norm();
    }
    Fraction(int x) {
        a = x;
        b = 1;
    }
    Fraction operator + (const Fraction& other) const {
        return Fraction(a * other.b + b * other.a, b * other.b);
    }
    Fraction operator - (const Fraction& other) const {
        return Fraction(a * other.b - b * other.a, b * other.b);
    }
    Fraction operator * (const Fraction& other) const {
        return Fraction(a * other.a, b * other.b);
    }
    Fraction operator / (const Fraction& other) const {
        assert(other.a != 0);
        return Fraction(a * other.b, b * other.a);
    }
    bool operator < (const Fraction& other) const {
        return a*other.b < b*other.a;
    }
    bool operator <= (const int& other) const {
        return (*this < other || *this == other);
    }
    bool operator > (const Fraction& other) const {
        return a*other.b > b*other.a;
    }
    bool operator == (const Fraction& other) const {
        return a*other.b == b*other.a;
    }
    bool operator != (const Fraction& other) const {
        return !(*this == other);
    }
    bool operator == (int& other) const {
        return a == b*other;
    }
    bool operator != (int& other) const {
        return !(*this == other);
    }
    void norm() {
        if (b < 0) {
            a = -a;
            b = -b;
        }
        if (a == 0) b = 1;
        else {
            int g = __gcd(llabs(a), llabs(b));
            a /= g;
            b /= g;
        }
    }
};
istream& operator >> (istream& cin, Fraction& p) {
    cin >> p.a;
    p.b = 1;
    return cin;
}
ostream& operator << (ostream& cout, Fraction& p) {
    cout << p.a << '/' << p.b;
    return cout;
}
Fraction abs(Fraction f) {
    f.a = abs(f.a);
    f.b = abs(f.b);
    return f;
}
