## Test details
- Most code in [library/](https://github.com/lrvideckis/programming_team_code/tree/master/library) *compiled* (no warnings) with [these flags](https://github.com/lrvideckis/programming_team_code/blob/master/tests/scripts/compile_flags.txt) from [Catching silly mistakes with GCC](https://codeforces.com/blog/entry/15547)
  - note `-Wconversion` is missing
  - see output of `make print_untested_files` for files which are not compiled
- [library_checker_tests/](https://github.com/lrvideckis/programming_team_code/tree/master/tests/library_checker_tests) which tests code on either [Library Checker](https://judge.yosupo.jp/) or [Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/home) ([steps to setup](https://online-judge-tools.github.io/verification-helper/installer.html))
  - Note: only 15 tests run at a time, and currently there are >40 tests. So if you have a big change (maybe code mod), only the first 15 lib-checker tests will run. To fix, I make random commits which change effectively nothing until all tests run.

## Makefile
to see commands:
```
make help
```
