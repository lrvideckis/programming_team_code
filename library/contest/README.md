## Tips and Tricks
- [C++ tips and tricks](https://codeforces.com/blog/entry/74684)
- use `#pragma GCC optimize "trapv"` to invoke RTE (Run Time Error) upon integer overflow
- use `mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());` to generate random integers

### Troubleshooting
```
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/
```
Author: Benq

- refer to KACTL Troubleshoot (linked below) for more details

## Sources

- [Don't use rand(): a guide to random number generators in C++](https://codeforces.com/blog/entry/61587)
- [Troubleshoot](https://github.com/kth-competitive-programming/kactl/blob/main/content/contest/troubleshoot.txt)
