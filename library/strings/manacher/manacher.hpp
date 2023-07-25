/** @file */
#pragma once
// https://codeforces.com/blog/entry/12143#comment-324162
// TODO: mention that i-th center has bounds [ man[i], i-man[i]+1 )
// and length  i - 2*man[i] + 1
template <class T> vector<int> manacher(const T& s) {
    int n = ssize(s);
    vector<int> man(max(0, 2*n - 1));
    for (int i = 0, p = 0, pR = 0/*-1*/; i < 2*n - 1; i++) {
        if(pR>=0) assert(p-man[p] == pR);
        int R = i <= 2*pR ? min(p - man[2*p - i], pR) : i/2;
        int L = i - R;
        assert((i <= 2*pR) == (i/2 <= pR));
        assert((i <= 2*pR) == (i <= 2*(p-man[p])));
        if(i > 2*pR) assert(L == (i+1)/2);
        else assert(L == i - p + max(man[2*p-i],man[p]));
        while (L > 0 && R < n-1 && s[L-1] == s[R+1]) {
            L--;
            R++;
            assert(R>pR);
        }
        man[i] = L;
        if (R > pR) {
            pR = R;
            p = i;
        }
        if(i==0) assert(p==0 && pR==0);
    }
    return man;
}
