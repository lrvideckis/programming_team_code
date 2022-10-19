## Testing
- We rely on online-judge-tools ([github](https://github.com/online-judge-tools/verification-helper)) which tests code on either [Library Checker](https://judge.yosupo.jp/) or [Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/courses/list) problems
  - [steps to setup](https://online-judge-tools.github.io/verification-helper/installer.html) for your own repo
- See `*.test.cpp` files in [online_judge_tests/](online_judge_tests/) for the actual tests
- Note: < 30 tests run per commit, and currently there are > 40 tests. So for big changes (ex: code mod), CI may not test all changed files. To fix, I make random commits which change effectively nothing until all tests run. Check [timestamps.remote.json](../.verify-helper/timestamps.remote.json) to see which tests ran
  - Trick: delete [timestamps.remote.json](../.verify-helper/timestamps.remote.json) to re-run all tests

## Linting
All of this *only* runs on `*.test.cpp` files in [online_judge_tests/](online_judge_tests/) (thus also *included* `*.hpp` files in [library/](../library/))
  - Reason: `*.hpp` files don't have includes (because CP) which the linters need. Also this way incentivizes adding tests. BTW kactl addresses this problem by [copying around / modifying](https://github.com/kth-competitive-programming/kactl/blob/main/doc/scripts/test-compiles.sh)  header files which I think is :vomiting_face:
  - see `make print_untested_files` for `*.hpp` files which are not included by any `*.test.cpp` file


tool | settings | notes | wiki
--- | --- | --- | ---
astyle | [.astylerc](.astylerc) | running `make check_format` locally will format files | http://astyle.sourceforge.net/astyle.html
cppcheck | see flags in cppcheck command in [scripts/check_format.sh](scripts/check_format.sh) | | https://cppcheck.sourceforge.io/
clang-tidy | [.clang-tidy](.clang-tidy) | checks variables for snake_case | https://clang.llvm.org/extra/clang-tidy/checks/list.html
g++ | [scripts/compile_flags.txt](scripts/compile_flags.txt) | `-std=c++17` since some judges still have this version; `-Werror` treats warnings as errors to make CI fail; inspiration: [Catching silly mistakes with GCC](https://codeforces.com/blog/entry/15547) |

## Makefile
to see commands:
```
make help
```
## Steps to add code from other repos to PDF
1. add other repo as a submodule
2. Include new file(s) in [scripts/hackpack.tex](scripts/hackpack.tex)
3. Add new file path(s) to [scripts/make_hackpack.sh](scripts/make_hackpack.sh) to include hash codes in PDF
4. build pdf
5. profit!
