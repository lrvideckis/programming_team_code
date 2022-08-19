## Test details
- Most code in [library/](https://github.com/lrvideckis/programming_team_code/tree/master/library) *compiled* (no warnings) with [these flags](https://github.com/lrvideckis/programming_team_code/blob/master/tests/scripts/compile_flags.txt) from [Catching silly mistakes with GCC](https://codeforces.com/blog/entry/15547)
  - note `-Wconversion` is missing
  - see output of `make print_untested_files` for files which are *not compiled, nor linted*
- [oj_tests/](https://github.com/lrvideckis/programming_team_code/tree/master/tests/oj_tests) which tests code on either [Library Checker](https://judge.yosupo.jp/) or [Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/home) ([steps to setup](https://online-judge-tools.github.io/verification-helper/installer.html))
  - Note: only 15 tests run at a time, and currently there are >40 tests. So if you have a big change (maybe code mod), only the first 15 lib-checker tests will run. To fix, I make random commits which change effectively nothing until all tests run.
  - need to specify config file when running locally:

```
oj-verify --config-file ~/programming_team_code/.verify-helper/config.toml run palindrome_query.test.cpp
```

## Makefile
to see commands:
```
make help
```
## Steps to add code from other repos to PDF
1. add other repo as a submodule
2. if the repo's root directory name isn't snake case, then update [this script](https://github.com/lrvideckis/programming_team_code/blob/master/tests/scripts/check_format.sh) to skip the new submodule
3. Include new file(s) in [PDF latex file](https://github.com/lrvideckis/programming_team_code/blob/master/tests/scripts/25_pg_reference.tex)
4. Add new file path(s) to [this script](https://github.com/lrvideckis/programming_team_code/blob/master/tests/scripts/make_pdf.sh) to include hash codes in PDF
5. build pdf
6. profit!
