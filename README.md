# Programming-Team-Code

Yet another competitive programming repo. Quick links:

- [Library/](https://github.com/lrvideckis/Programming-Team-Code/tree/master/Library) for copy-pastable c++ code
- [template.cpp](https://github.com/lrvideckis/Programming-Team-Code/blob/master/template.cpp)

## Testing

- All code compiled (no warnings) with: `g++ -Wall -Wextra -pedantic -Wno-unused-result -Wfatal-errors -DLOCAL -std=c++17 -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wcast-qual -Wcast-align -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fstack-protector` from [Catching silly mistakes with GCC](https://codeforces.com/blog/entry/15547)
  - note `-Wconversion` is missing
- [tests/library-checker-tests/](https://github.com/lrvideckis/Programming-Team-Code/tree/master/library-checker-tests) which tests code on [Library Checker](https://judge.yosupo.jp/) ([steps to setup](https://online-judge-tools.github.io/verification-helper/installer.html))
- [tests/stress-tests/](https://github.com/lrvideckis/Programming-Team-Code/tree/master/stress-tests) which compares library code output to a naive version (or another alg) on random inputs.
-  Not all code is tested; see test status comments at the top of each file.

## Format
Run the following from [Library/](https://github.com/lrvideckis/Programming-Team-Code/tree/master/Library) to format. [astyle wiki](http://astyle.sourceforge.net/astyle.html)
```
astyle --recursive "*.h" --indent=tab --remove-braces --style=attach --align-reference=type --align-pointer=type --delete-empty-lines --attach-classes --pad-oper --pad-header --unpad-paren --close-templates
```

## License

Everything is under [CC0](https://creativecommons.org/publicdomain/zero/1.0/).

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
- [Sqrt decomposition](https://github.com/nealwu/competitive-programming/blob/master/sqrt/search_buckets.cc) (search buckets)
- [fast IO](https://github.com/nealwu/competitive-programming/blob/master/io/io.cc)
