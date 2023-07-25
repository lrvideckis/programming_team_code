/** @file */
#pragma once
// https://codeforces.com/blog/entry/12143#comment-324162
// TODO: mention that i-th center has bounds [ man[i], i-man[i]+1 )
// and length  i - 2*man[i] + 1
template <class T> vector<int> manacher(const T& s) {
    int n = ssize(s);
    vector<int> man(max(0, 2*n - 1));
    auto ri = [&](int i) -> int {return i - man[i];};
    for (int i = 0, p = 0; i < 2*n - 1; i++) {
        man[i] = i <= 2*ri(p) ? i - p + max(man[2*p-i],man[p])) : (i+1)/2;
        while (man[i] > 0 && ri(i) < n-1 && s[man[i]-1] == s[ri(i)+1])
            man[i]--, p=i;
    }
    return man;
}
