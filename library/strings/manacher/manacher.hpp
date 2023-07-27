/** @file */
#pragma once
// https://codeforces.com/blog/entry/12143#comment-324162
// TODO: mention that i-th center has bounds [ man[i], i-man[i]+1 )
// and length  i - 2*man[i] + 1
template <class T> vector<int> manacher(const T& s) {
    int n = ssize(s);
    vector<int> man(max(0, 2 * n - 1));
    for (int i = 0, p = 0; i < 2 * n - 1; i++) {
        int ri = i <= 2 * (p - man[p]) ? p - max(man[2 * p - i], man[p]) : i / 2;
        man[i] = i - ri;
        while (man[i] > 0 && ri < n - 1 && s[man[i] - 1] == s[ri + 1])
            man[i]--, ri++, p = i;
    }
    return man;
}
