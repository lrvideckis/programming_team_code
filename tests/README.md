## Test details
- All code in [library/](https://github.com/lrvideckis/programming_team_code/tree/master/library) except [these](https://github.com/lrvideckis/programming_team_code/blob/master/tests/scripts/skip_headers.txt) *compiled* (no warnings) with [these flags](https://github.com/lrvideckis/programming_team_code/blob/master/tests/scripts/compile_flags.txt) from [Catching silly mistakes with GCC](https://codeforces.com/blog/entry/15547)
  - note `-Wconversion` is missing
- [library_checker_tests/](https://github.com/lrvideckis/programming_team_code/tree/master/tests/library_checker_tests) which tests code on [Library Checker](https://judge.yosupo.jp/) ([steps to setup](https://online-judge-tools.github.io/verification-helper/installer.html))
  - Note: only 15 tests run at a time, and currently there are 30 tests. So if you have a big change (maybe code mod), only the first 15 lib-checker tests will run. To fix, I make random commits which change effectively nothing until all tests run.
- [stress_tests/](https://github.com/lrvideckis/programming_team_code/tree/master/tests/stress_tests) which compares library code output to a naive version (or another alg) on random inputs.

## Test status comments

Each file has 2 standardized comments displaying test status (checked by CI):
- `//library checker tests: https://judge.yosupo.jp/problem/..., https://judge.yosupo.jp/problem/...`
- `//stress tests: tests/stress-tests/<path_to_test_1>, tests/stress-tests/<path_to_test_2>`

## Makefile
to see commands:
```
make help
```
