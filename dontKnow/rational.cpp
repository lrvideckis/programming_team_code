struct rat {
    ll top;
    ll bot;
};

bool operator<(const rat& x, const rat& y) {
    return x.top * y.bot < y.top * x.bot;
}

void simplify(rat& r) {
    ll gcd = __gcd(r.top, r.bot);
    r.top /= gcd;
    r.bot /= gcd;

    if(r.bot < 0) {
        r.top *= -1;
        r.bot *= -1;
    }

    if(r.top == 0) {
        r.bot = 1;
    }

    if(r.bot == 0) {
        r.top = 1;
    }
}

rat mul(rat r1, rat r2) {
    simplify(r1);
    simplify(r2);
    rat ret = {r1.top * r2.top, r1.bot * r2.bot};
    simplify(ret);
    return ret;
}

rat mul(rat r1, ll i) {
    return mul(r1,{i,1});
}

rat div(rat r1, rat r2) {
    simplify(r1);
    simplify(r2);
    rat ret = {r1.top * r2.bot, r1.bot * r2.top};
    simplify(ret);
    return ret;
}

rat div(rat r1, ll i) {
    return div(r1,{i,1});
}

rat add(rat r1, rat r2) {
    simplify(r1);
    simplify(r2);

    ll bot1 = r1.bot;
    ll bot2 = r2.bot;

    r1.top *= bot2;
    r1.bot *= bot2;

    r2.top *= bot1;
    r2.bot *= bot2;

    rat r = {r1.top + r2.top, r1.bot};
    simplify(r);
    return r;
}

rat add(rat r1, ll i) {
    return add(r1,{i,1});
}

rat sub(rat r1, rat r2) {
    simplify(r1);
    simplify(r2);

    ll bot1 = r1.bot;
    ll bot2 = r2.bot;

    r1.top *= bot2;
    r1.bot *= bot2;

    r2.top *= bot1;
    r2.bot *= bot2;

    rat r = {r1.top - r2.top, r1.bot};
    simplify(r);
    return r;
}

rat sub(rat r1, ll i) {
    return sub(r1,{i,1});
}

rat perpendicular(rat r) {
    simplify(r);
    rat ret = {-r.bot, r.top};
    simplify(ret);
    return ret;
}

rat abs(rat r) {
    simplify(r);
    if(r.top < 0) {
        r.top *= -1;
    }
    simplify(r);
    return r;
}

ostream& operator<<(ostream& o, const rat& r) {
    return o << r.top << "/" << r.bot;
}
