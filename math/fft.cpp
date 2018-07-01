#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef complex<double> cd;

const int Log = 19, Max = 1 << Log;
const double pi = 4*atan(1.0);
cd root[Max], arrA[Max], arrB[Max];
int perm[Max];

void fft(cd* arr) {
    for(int i = 0; i < Max; i++) {
        if(i < perm[i]) {
            swap(arr[i], arr[perm[i]]);
        }
    }
    for(int len = 1; len < Max; len *= 2) {
        for(int pos = 0; pos < Max; pos += 2 * len) {
            for(int i = 0; i < len; i++) {
                cd x = arr[pos + i], y = arr[pos + i + len] * root[Max / len / 2 * i];
                arr[pos + i] = x + y;
                arr[pos + i + len] = x - y;
            }
        }
    }
}

void mult(int* a, int* b, ll* ans) {
    for(int i = 0; i < Max; i++) {
        arrA[i] = cd(a[i], 0);
        arrB[i] = cd(b[i], 0);
    }
    fft(arrA);
    fft(arrB);
    for(int i = 0; i < Max; i++) {
        arrA[i] *= arrB[i];
    }
    fft(arrA);
    reverse(arrA + 1, arrA + Max);
    for(int i = 0; i < Max; i++) {
        arrA[i] /= Max;
        ans[i] = (ll)(round(arrA[i].real()));
    }
}

void pre_proc() {
    int hb = -1;
    root[0] = 1;
    double angle = 2 * pi / Max;
    for(int i = 1; i < Max; i++) {
        if((i & (i - 1)) == 0) hb++;
        root[i] = cd(cos(angle * i), sin(angle * i));
        perm[i] = perm[i ^ (1 << hb)] + (1 << (Log - hb - 1));
    }
}

int a[Max] = {0}, b[Max] = {0};
ll prod[Max];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    pre_proc();
    int sizeA;
    cin >> sizeA;
    cin >> sizeA;
    for(int i = 0; i <= sizeA; ++i) {
        cin >> a[i];
    }
    int sizeB;
    cin >> sizeB;
    for(int i = 0; i <= sizeB; ++i) {
        cin >> b[i];
    }
    mult(a, b, prod);
    cout << sizeA+sizeB << '\n';
    for(int i = 0; i <= sizeA+sizeB; ++i) cout << prod[i] << ' ';cout << '\n';
    return 0;
}


