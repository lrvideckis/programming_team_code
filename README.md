# Programming-Team-Code

Yet another competitive programming repo. Directory structure inspired by [KACTL](https://github.com/kth-competitive-programming/kactl):

- [content/](https://github.com/lrvideckis/Programming-Team-Code/tree/master/content) for copy-pastable c++ code
- [template.cpp](https://github.com/lrvideckis/Programming-Team-Code/blob/master/template.cpp), although all code *should* work with just `typedef long long ll;`
  - Note the `#define int long long` -> WA from overflow too many times 😅. All [existing tests](https://github.com/lrvideckis/Programming-Team-Code/tree/master/stress-tests) are [compiled without](https://github.com/lrvideckis/Programming-Team-Code/blob/master/stress-tests/test_utilities/template.h) this `#define`, so feel free to remove it.

## Testing

- All code compiled with flags: `g++ -Wall -Wextra -pedantic -Wno-unused-result -Wfatal-errors -DLOCAL -std=c++17 -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wcast-qual -Wcast-align -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fstack-protector` from [Catching silly mistakes with GCC](https://codeforces.com/blog/entry/15547)
  - note `-Wconversion` is missing
- *Most* code submitted on various online judges (in particular [Library Checker](https://judge.yosupo.jp/))
- [stress-tests](https://github.com/lrvideckis/Programming-Team-Code/tree/master/stress-tests) which compares library code output to a naive version (or another alg) on random inputs (run with CI on every commit).

## Coding style

I aim for a balance between best coding practices, speed (runtime), and ease of modifiability.

- minimal `#define`'s and `typedef`'s for ease of use & readability & modifiability
- prefering structs & functions over globals to keep a clean scope
- [tabs](https://youtu.be/SsoOG6ZeyUI) (fight me)

## Out of scope

- [Geometry](https://github.com/kth-competitive-programming/kactl/tree/main/content/geometry)
- [Fast Fourier transform](https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/FastFourierTransform.h)
- [2-sat](https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/2sat.h)
- [Chinese Remainder Theorem](https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/CRT.h)
- [Convex Hull Trick](https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h)
- [Miller Rabin](https://github.com/kth-competitive-programming/kactl/blob/main/content/number-theory/MillerRabin.h)
- [Longest Increasing Subsequence](https://github.com/kth-competitive-programming/kactl/blob/main/content/various/LIS.h)
- [Z function](https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/Zfunc.h)
- [Manacher's](https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/Manacher.h)
- [Sqrt decomposition](https://github.com/nealwu/competitive-programming/blob/master/sqrt/search_buckets.cc)
