/** @file */
#pragma once
// https://codeforces.com/blog/entry/12143#comment-324162
// TODO: mention that i-th center has bounds [ man[i], i-man[i]+1 )
// and length  i - 2*man[i] + 1
template <class T> vector<int> manacher(const T& s) {
    int n = ssize(s);
    vector<int> res(max(0, 2*n - 1));
    int p = 0, pR = -1;
    for (int pos = 0; pos < 2*n - 1; pos++) {
        if(pR>=0) assert(p-res[p] == pR);
        int R = pos <= 2*pR ? min(p - res[2*p - pos], pR) : pos/2;
        int L = pos - R;

        while (L > 0 && R < n-1 && s[L-1] == s[R+1]) {
            L--;
            R++;
            assert(R>pR);
        }
        res[pos] = L;
        if (R >= /*revert*/ pR) {
            pR = R;
            p = pos;
        }
    }
    return res;
}
