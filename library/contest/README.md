## Tips and Tricks

- use `#pragma GCC optimize "trapv"` to invoke RTE (Run Time Error) upon integer overflow
- use `mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());` to generate random integers

## Sources

- [Don't use rand(): a guide to random number generators in C++](https://codeforces.com/blog/entry/61587)
