## Testing
- Most code in [library/](https://github.com/lrvideckis/programming_team_code/tree/master/library) *compiled* (no warnings) with [these flags](https://github.com/lrvideckis/programming_team_code/blob/master/tests/scripts/compile_flags.txt) inspired by [Catching silly mistakes with GCC](https://codeforces.com/blog/entry/15547)
  - note `-Wconversion` is missing
  - see output of `make print_untested_files` for files which are *not compiled, nor linted*
- [online_judge_tests/](https://github.com/lrvideckis/programming_team_code/tree/master/tests/online_judge_tests) which tests code on either [Library Checker](https://judge.yosupo.jp/) or [Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/courses/list) ([steps to setup](https://online-judge-tools.github.io/verification-helper/installer.html)) ([online-judge-tools github](https://github.com/online-judge-tools/verification-helper))
  - Note: only 30 tests run at a time, and currently there are >40 tests. So if you have a big change (maybe code mod), only the first 30 lib-checker tests will run. To fix, I make random commits which change effectively nothing until all tests run.
  - need to specify config file when running locally:

```
oj-verify --config-file ~/programming_team_code/.verify-helper/config.toml run palindrome_query.test.cpp
```

## Linting
tool | settings | notes | wiki
--- | --- | --- | ---
astyle | [.astylerc](https://github.com/lrvideckis/programming_team_code/blob/master/tests/.astylerc) | running `make check_format` locally will format files | http://astyle.sourceforge.net/astyle.html
clang-tidy | [.clang-tidy](https://github.com/lrvideckis/programming_team_code/blob/master/tests/.clang-tidy) | checks variables for snake_case | https://clang.llvm.org/extra/clang-tidy/checks/list.html
cppcheck | see flags in cppcheck command in [check_format.sh](https://github.com/lrvideckis/programming_team_code/blob/master/tests/scripts/check_format.sh) | | https://cppcheck.sourceforge.io/
g++ | [compile_flags.txt](https://github.com/lrvideckis/programming_team_code/blob/master/tests/scripts/compile_flags.txt) | |

## Makefile
to see commands:
```
make help
```
## Steps to add code from other repos to PDF
1. add other repo as a submodule
2. Include new file(s) in [PDF latex file](https://github.com/lrvideckis/programming_team_code/blob/master/tests/scripts/hackpack.tex)
3. Add new file path(s) to [this script](https://github.com/lrvideckis/programming_team_code/blob/master/tests/scripts/make_hackpack.sh) to include hash codes in PDF
4. build pdf
5. profit!
