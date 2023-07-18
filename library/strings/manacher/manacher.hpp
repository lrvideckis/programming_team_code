/** @file */
#pragma once
// https://codeforces.com/blog/entry/12143#comment-324162
vector<int> manacher(const string& s) {
    const int n = (int)s.length();
    if (n == 0)
        return vector<int>();
    vector<int> res(2*n - 1);
    int p = 0, pR = -1;
    for (int pos = 0; pos < 2*n - 1; ++pos) {
        int R = pos <= 2*pR ? min(p - res[2*p - pos], pR) : pos/2;
        int L = pos - R;
        while (L > 0 && R < n-1 && s[L-1] == s[R+1]) {
            --L;
            ++R;
        }
        res[pos] = L;
        if (R > pR) {
            pR = R;
            p = pos;
        }
    }
    return res;
}
