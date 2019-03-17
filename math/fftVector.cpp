#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef complex<double> cd;

const int Max = 1e6+10;
int bound, logBound;
const double pi = 4*atan(1.0);
cd root[Max], arrA[Max], arrB[Max];
int perm[Max];
ll prod[Max];

void fft(cd* arr) {
    for(int i = 0; i < bound; i++) {
        if(i < perm[i]) {
            swap(arr[i], arr[perm[i]]);
        }
    }
    for(int len = 1; len < bound; len *= 2) {
        for(int pos = 0; pos < bound; pos += 2 * len) {
            for(int i = 0; i < len; i++) {
                cd x = arr[pos + i], y = arr[pos + i + len] * root[bound / len / 2 * i];
                arr[pos + i] = x + y;
                arr[pos + i + len] = x - y;
            }
        }
    }
}

void preCalc() {
    int hb = -1;
    root[0] = 1;
    double angle = 2 * pi / bound;
    for(int i = 1; i < bound; i++) {
        if((i & (i - 1)) == 0) hb++;
        root[i] = cd(cos(angle * i), sin(angle * i));
        perm[i] = perm[i ^ (1 << hb)] + (1 << (logBound - hb - 1));
    }
}

void mult(const vector<int> &a, const vector<int> &b, vector<ll> &c) {
    logBound = 0;
    while((1<<logBound) < a.size() || (1<<logBound) < b.size()) logBound++;
    logBound++;
    bound = (1<<logBound);
    preCalc();
    for(int i = 0; i < a.size(); i++) {
        arrA[i] = cd(a[i], 0);
    }
    for(int i = a.size(); i < bound; i++) {
        arrA[i] = cd(0, 0);
    }
    for(int i = 0; i < b.size(); i++) {
        arrB[i] = cd(b[i], 0);
    }
    for(int i = b.size(); i < bound; i++) {
        arrB[i] = cd(0, 0);
    }
    fft(arrA);
    fft(arrB);
    for(int i = 0; i < bound; i++) {
        arrA[i] *= arrB[i];
    }
    fft(arrA);
    reverse(arrA + 1, arrA + bound);
    c.resize(bound);
    for(int i = 0; i < bound; i++) {
        arrA[i] /= bound;
        ll temp = (arrA[i].real() > 0 ? arrA[i].real()+.5 : arrA[i].real() - .5);
        c[i] = temp;
    }
    while(c.size() && c.back() == 0) c.pop_back();
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    cin >> n;
    vector<int> a(n+1);
    for(int i = 0; i <= n; ++i) {
        cin >> a[i];
    }
    cin >> n;
    vector<int> b(n+1);
    for(int i = 0; i <= n; ++i) {
        cin >> b[i];
    }
    vector<ll> c;
    mult(a, b, c);
    cout << c.size()-1 << '\n';
    for(int coef : c) {
        cout << coef << ' ';
    }
    cout << '\n';
    return 0;
}
















